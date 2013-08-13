#ifndef CW_CORE_CONFIG_HPP_INC
#define CW_CORE_CONFIG_HPP_INC

#include <string>
#include <istream>
#include <unordered_map>
#include <vector>

namespace cw
{
  namespace core
  {
    namespace helper
    {
      std::vector<std::string> split(const std::string &line, char delimiter);
      std::string strip(std::string line);
    }

    /**
     *  Represents one config node, which can have key => value pairs
     */
    class Node
    {
      public:
        typedef std::string Property;
        typedef std::string Key;
        typedef std::unordered_map< Key, Property > DefaultValueMap;

        Node();
        static Node createFromDefaultValues(const DefaultValueMap &);

        // return value is undefined if key does not exist
        const Property & operator[](const Key& key) const;

      protected:
        friend class Config;

        void parseProperties(std::istream & in);
      private:
        typedef DefaultValueMap ValueMap;
        ValueMap m_values;

    };

    /**
     *  Represents the whole config, contains Node-s, indexed by their name
     */
    class Config
    {
      public:
        typedef std::unordered_map< std::string, Node::DefaultValueMap > DefaultConfigMap;

        Config(std::istream & in);
        ~Config();

        const Node & getNode(const std::string & nodeName) const;
        const Node * getNodePtr(const std::string & nodeName) const;
      private:
        void loadDefaultConfig();
        void parseStream(std::istream & in);

        Node * getNodePtr(const std::string & nodeName);

        std::unordered_map< std::string, Node > m_nodes;
    };
  }
}

#endif
