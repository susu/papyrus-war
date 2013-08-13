#include <igloo/igloo_alt.h>

#include <cw/core/Config.hpp>

using namespace igloo;
using namespace cw;

Describe(AConfig)
{
  Describe(config_helper_functions)
  {
    It(has_split_function)
    {
      using namespace core::helper;
      std::vector<std::string> expected = {"whatever"," you want"};
      AssertThat(split("whatever: you want",':'), EqualsContainer(expected));
    }

    It(has_strip_function)
    {
      using namespace core::helper;
      AssertThat(strip("heyho"), Equals("heyho"));
      AssertThat(strip("     forty-two"), Equals("forty-two"));
      AssertThat(strip("trailing    "), Equals("trailing"));
      AssertThat(strip("multiple word in one string"),
                Equals("multiple word in one string"));
      AssertThat(strip(" x  "), Equals("x"));
    }
  };

  Describe(screen_config)
  {
    std::stringstream in;
    It(has_default_properties)
    {
      in << "screen {" << std::endl
         << "}" << std::endl;

      core::Config config(in);

      const core::Node & node = config.getNode("screen");
      AssertThat(node["resolution"], Equals("auto"));
      AssertThat(node["monitor"], Equals("primary"));
      AssertThat(node["fullscreen"], Equals("yes"));
    }

    It(can_be_defined)
    {
      in << "screen {" << std::endl
         << "  resolution: 1920x1080" << std::endl
         << "}" << std::endl;

      core::Config config(in);
      const core::Node & node = config.getNode("screen");

      AssertThat(node["resolution"], Equals("1920x1080"));
    }
  };
};
