from pygccxml import utils
from pygccxml import declarations
from pygccxml import parser

# Find the location of the xml generator (castxml or gccxml)
generator_path, generator_name = utils.find_xml_generator()

print 'generator_path:', generator_path
print 'generator_name:', generator_name

# Configure the xml generator
xml_generator_config = parser.xml_generator_configuration_t(
    xml_generator_path=generator_path,
    xml_generator=generator_name)

# The c++ file we want to parse
filename = "example.hpp"

# Parse the c++ file
decls = parser.parse([filename], xml_generator_config)

# Get access to the global namespace
global_namespace = declarations.get_global_namespace(decls)

# Get access to the 'ns' namespace
ns = global_namespace.namespace("ns")
