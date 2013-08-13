#include <cw/core/Config.hpp>

#include <cw/Enforce.hpp>
#include <cw/core/Logger.hpp>

namespace cw
{
  namespace core
  {
    namespace helper
    {
      std::vector<std::string> split(const std::string &line, char delimiter)
      {
        std::vector<std::string> result;
        size_t lastIndex = 0;
        size_t index = line.find(delimiter);
        result.push_back(line.substr(lastIndex, index));

        while(index != std::string::npos)
        {
          lastIndex = index+1;
          index = line.find(delimiter, index+1);
          result.push_back(line.substr(lastIndex, index));
        }
        return result;
      }

      static const char * WHITESPACES = " \n\t\r";
      std::string strip(std::string line)
      {
        auto start = line.find_first_not_of(WHITESPACES);
        if (std::string::npos == start)
          start = 0;

        auto end = line.find_last_not_of(WHITESPACES);
        if (std::string::npos == end)
          end = line.length();

        return line.substr(start, end-start+1);
      }
    } // namespace helper

const static Config::DefaultConfigMap g_defaultConfig =
{
  {"screen", Node::DefaultValueMap(
    {
      // TODO define validators
      {"resolution", "auto"},
      {"monitor", "primary"},
      {"fullscreen", "yes"},
    })
  }
};

// ---- Config ----

Config::Config(std::istream & in)
{
  loadDefaultConfig();

  parseStream(in);
}

Config::~Config()
{}

void Config::loadDefaultConfig()
{
  m_nodes.clear();
  for (const auto & x : g_defaultConfig)
  {
    LOG_INFO("Adding node: ", x.first);
    m_nodes[x.first] = Node::createFromDefaultValues(x.second);
  }
}

void Config::parseStream(std::istream & in)
{
  std::string line;
  std::getline(in, line);
  LOG_DEBUG("  line: '",line, "'");

  auto parts = helper::split(line, ' ');
  std::string nodeName = parts[0];
  LOG_INFO("node-name acquired: ", nodeName);

  Node * node = getNodePtr(nodeName);
  ENFORCE(node != nullptr, "Unknown node:"+nodeName);
  LOG_DEBUG("node-name valid: '", nodeName, "'");

  node->parseProperties(in);

  while(in.good())
  {
    std::getline(in, line);
    LOG_DEBUG("  line: '",line, "'");
  }
}

const Node& Config::getNode(const std::string & nodeName) const
{
  auto it = m_nodes.find(nodeName);
  ENFORCE(it != m_nodes.end(), "No such node: "+nodeName);
  return it->second;
}

const Node* Config::getNodePtr(const std::string & nodeName) const
{
  auto it = m_nodes.find(nodeName);
  if (it == m_nodes.end())
    return nullptr;
  return &it->second;
}

Node * Config::getNodePtr(const std::string & nodeName)
{
  auto it = m_nodes.find(nodeName);
  if (it == m_nodes.end())
    return nullptr;
  return &it->second;
}

// ---- Node ----

Node::Node()
{}

Node Node::createFromDefaultValues(const DefaultValueMap & values)
{
  Node n;
  n.m_values = values;
  return n;
}

bool endOfNode(const std::string & line)
{
  auto index = line.find('}');
  if (index == std::string::npos)
    return false;
  return true;
}

void Node::parseProperties(std::istream & in)
{
  std::string line;
  getline(in, line);
  LOG_DEBUG("line(node parsing): '", line, "'");

  while( !endOfNode(line) )
  {
    auto parts = helper::split(line, ':');
    std::string propertyName = helper::strip(parts[0]);
    std::string propertyValue = helper::strip(parts[1]);

    LOG_DEBUG("prop.name: '", propertyName, "', value: '", propertyValue, "'");
    m_values[propertyName] = propertyValue;
    getline(in, line);
    LOG_DEBUG("line(node parsing): '", line, "'");
  }

  LOG_DEBUG("End of node parsing.");
}

const Node::Property & Node::operator[](const Key & key) const
{
  auto it = m_values.find(key);
  ENFORCE(it != m_values.end(), std::string("No such key: ") + key);
  return it->second;
}

  }
}
