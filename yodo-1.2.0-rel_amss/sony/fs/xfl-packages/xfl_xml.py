#!/usr/bin/env python
import os,sys
import xml.dom.minidom
import optparse
from xml.dom.minidom import parse


def parse_jenkins_config_xml(config_xml_path):
    matrix_dom_tree = xml.dom.minidom.parse(config_xml_path)
    matrix_project = matrix_dom_tree.documentElement
    package_names_list=[]

    TextAxis = matrix_project.getElementsByTagName("hudson.matrix.TextAxis")
    for text in TextAxis:
        name = text.getElementsByTagName("name")[0]
        if name.childNodes[0].data == "HUDSON_PRODUCT":
            package_group_names = text.getElementsByTagName("string")

    for string in package_group_names:
        package_names_list.append(string.childNodes[0].data)

    return package_names_list


def modify_package_xml(package_xml_path, package_names_list, new_deb_revision):
    xfl_dom_tree = xml.dom.minidom.parse(package_xml_path)
    xfl_project =  xfl_dom_tree.documentElement

    package_groups = xfl_project.getElementsByTagName("package-group")
    for package_group in package_groups:
        name = package_group.getAttribute("name")
        if name in package_names_list:
            package_group.attributes["revision"].value = new_deb_revision
            revision = package_group.getAttribute("revision")
            package_names_list.remove(name)

    for package_name in package_names_list:
        pk_group = xfl_dom_tree.createElement("package-group")
        pk_group.setAttribute("name", package_name)
        pk_group.setAttribute("revision", new_deb_revision)
        package = xfl_dom_tree.createElement("package")
        package.setAttribute("name", "fw-xfl-%s" % package_name.replace("_", "-"))
        pk_group.appendChild(package)
        xfl_dom_tree.childNodes[0].appendChild(pk_group)

    open(package_xml_path, "wb").write(xfl_dom_tree.toprettyxml(encoding="UTF-8"))

def main(argv):
    parser = optparse.OptionParser("%prog JENKINS_BUILD_MATRIX_CONFIG_XML "
                                   "XFL_PACKAGE_XML "
                                   "NEW_DEB_PACKAGE_REVISION ")
    (options, args) = parser.parse_args()
    if len(args) < 3:
        parser.print_usage(file=sys.stderr)
        sys.exit(1)

    jenkins_config_xml_path = args[0]
    xfl_package_xml_path = args[1]
    new_deb_revision = args[2]

    package_names = parse_jenkins_config_xml(jenkins_config_xml_path)
    modify_package_xml(xfl_package_xml_path, package_names, new_deb_revision)
    cmd = "xmllint --format " + xfl_package_xml_path + " --output " + xfl_package_xml_path
    os.system(cmd)

if __name__ == '__main__':
    main(sys.argv[:])
