#============================================================================
#
# @file DTSParser.py
#
# GENERAL DESCRIPTION
#   Unified script for generating static register setting from dts file
#
# Copyright 2019 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#
#----------------------------------------------------------------------------

import sys
import re
from collections import OrderedDict


class Node:
    def __init__(self, name):
        self.name = name
        self.prefix_name = None
        self.addr = None
        self.property = {}
        self.child = []
        self.parent = None
        self.start_index = 0
        self.end_index = 0

    def show(self):
        print(self.name, self.addr)
        # for f in self.property.items():
        #     print(f)


class BraceInfo:
    def __init__(self, index, brace, node):
        self.index = index
        self.brace = brace
        self.node = node

    def show(self):
        print(self.index, self.brace, self.node)


class DTSParser:
    special_char_set = {';', '{', '}'}

    def __init__(self, dts_file_name):
        self.dts_data = None
        self.dts_cur_parse_index = 0
        self.current_node_level = 0
        self.brace_info_list = []
        self.converted_node_list = []
        with open(dts_file_name, "r") as f:
            self.dts_data = f.read()

        '''remove all comments in this DTS file
        Remove string that start with '/*' abd end with '*/' and also
        insde it should not contain any '/*' and '*/'
        Do muitiple times until cannot find '/*', thus all comments should be removed
        '''
        m = re.compile(r'/\*((?!/\*|\*/).)*\*/', re.S)
        while (self.dts_data.find(r'/*') >= 0):
            self.dts_data = re.sub(m, '', self.dts_data)

        '''Remove line that start wtih #'''
        self.dts_data = re.sub(r'.*#include.*[\n|(\r\n)]', '', self.dts_data)

        self.__craete_brace_info_list()

    '''
    This function will remove the bracket which is at the begining and end of the string
    then split the string with space and convert the string to list
    Note: this funciton is only suitable to convert string like: qcom,sde-vbif-memtype-0 = <3 3 3 3 3 3 3 3> or qcom,sde-vbif-id = <0>
    But it is not suitable to convert string like: 		reg = <0x0ae00000 0x84208>, <0x0aeb0000 0x2008>
    '''

    @staticmethod
    def convert_str2list(s):
        list = None

        if s.startswith("<") and s.endswith(">"):
            list = re.sub(r'[<>]', '', s).split()
            for i in range(len(list)):
                if list[i].startswith("0x"):
                    list[i] = int(list[i], 16)
                else:
                    list[i] = int(list[i], 10)
        elif s.startswith("[") and s.endswith("]"):
            list = re.sub('[\[\]]', '', s).split()
            for i in range(len(list)):
                list[i] = int(list[i], 16)

        return list

    def __craete_brace_info_list(self):
        for i in range(len(self.dts_data)):
            c = self.dts_data[i]
            if (c == '{' or c == '}'):
                self.brace_info_list.append(BraceInfo(i, c, None))

    def __show_brace_info_list(self):
        for info in self.brace_info_list:
            self.show_brace_info(info)

    def __deep_strip(self, s):
        '''remove \t \n \r'''
        return re.sub(r'[\t\n\r]', ' ', s).strip()

    def __convert_buffer_to_node(self, data):
        """
        example input format like below:
        qcom,platform-supply-entry@0 {
                qcom,supply-name ="mmcx";
                qcom,supply-min-voltage = <0>;
            };
        """
        left_brace_index = data.index('{')
        right_brace_index = data.index('}')
        '''Name maybe like: 'mdss_mdp: qcom,mdss_mdp@ae00000' '''
        node_prefix_name = None
        node_name = None
        node_addr = None

        '''get node address'''
        total_name = data[:left_brace_index].split('@')
        if (len(total_name) >= 2):
            node_addr = total_name[-1].strip()

        '''get node prefix name and address'''
        total_name = total_name[0].split(':')
        if (len(total_name) >= 2):
            node_prefix_name = total_name[0].strip()
        node_name = total_name[-1].strip()

        items = data[left_brace_index + 1:right_brace_index].split(';')
        node = Node(node_name)
        node.prefix_name = node_prefix_name
        node.addr = node_addr

        for item in items:
            _item = item.split('=')
            if len(_item) >= 2:
                key = self.__deep_strip(_item[0].replace("\"", ""))
                val = self.__deep_strip(_item[1].replace("\"", ""))
                node.property[key] = val
        return node

    def __parse_leaf_node(self):
        removed_brace_list = []
        for i in range(len(self.brace_info_list) - 1):
            left_brace = self.brace_info_list[i]
            right_brace = self.brace_info_list[i + 1]
            if left_brace.brace == '{' and left_brace.node == None and right_brace.brace == '}' and right_brace.node == None:
                '''Go back from left brace to get the node name'''
                index = left_brace.index - 1
                while index > 0 and self.dts_data[index] not in DTSParser.special_char_set:
                    index = index - 1
                index = index + 1
                node_start_index = index
                node_end_index = right_brace.index + 1

                '''Check inside all currently converted node and tag the one that is inside current node'''
                top_parent_node_list = []
                reconstruct_data_index = [node_start_index, node_end_index]
                for node in self.converted_node_list:
                    '''Go to the top parent node'''
                    node = self.get_top_parent_node(node)
                    if node in top_parent_node_list:
                        continue
                    if node.start_index >= node_start_index and node.end_index <= node_end_index:
                        top_parent_node_list.append(node)
                        reconstruct_data_index.append(node.start_index)
                        reconstruct_data_index.append(node.end_index)

                '''construct data that removed all sub-nodes data'''
                reconstruct_data_index.sort()
                data = ""
                for i in range(0, len(reconstruct_data_index), 2):
                    data = data + dtsParser.dts_data[reconstruct_data_index[i]: reconstruct_data_index[i + 1]]

                '''node data is ready now'''
                new_node = self.__convert_buffer_to_node(data)
                new_node.start_index = node_start_index
                new_node.end_index = node_end_index
                left_brace.node = new_node
                right_brace.node = new_node
                for n in top_parent_node_list:
                    n.parent = new_node
                    new_node.child.append(n)

                '''brace info will be added to converted_node_list and deleted from  brace_info_list'''
                self.converted_node_list.append(new_node)
                removed_brace_list.append(left_brace)
                removed_brace_list.append(right_brace)

        '''update brace_info_list'''
        for brace_info in removed_brace_list:
            self.brace_info_list.remove(brace_info)

    def parse_all_nodes(self):
        while (len(self.brace_info_list) > 0):
            self.__parse_leaf_node()

    def get_node_by_name(self, node_name):
        """Be careful that some sub node has same name"""
        ret_node = []
        for node in self.converted_node_list:
            if node.name == node_name:
                ret_node.append(node)
        '''If found multiple nodes, return the list, otherwise return the only node'''
        if (len(ret_node) > 1):
            return ret_node
        elif (len(ret_node) == 1):
            return ret_node[0]
        else:
            return None

    '''
    This function is for property group like, :
    reg = <0x0ae00000 0x84208>, <0x0aeb0000 0x2008>
	reg-names = "mdp_phys", "vbif_phys"
	'''

    def get_reg_info_by_name(self, node, reg, reg_names, target_name):
        if node == None:
            return None

        name_str = node.property[reg_names]
        val_str = node.property[reg]
        if (name_str != None and val_str != None):
            name_list = name_str.split(',')
            val_list = val_str.split(',')
            if len(name_list) != len(val_list):
                return None
            for i in range(len(name_list)):
                if name_list[i].strip() == target_name:
                    ret_val = val_list[i].strip()
                    '''<> are default for Integers, [] are for hex values'''
                    return self.convert_str2list(ret_val)

    def get_top_parent_node(self, node):
        while (node.parent):
            node = node.parent
        return node

    def get_property(self, node, prop_name):
        if node == None:
            return None
        elif prop_name not in node.property.keys():
            return None
        elif len(node.property[prop_name]) <= 0:
            return None
        return self.convert_str2list(node.property[prop_name])

    def walk_nodes(self, start_node):
        """Walk through all nodes with BFS"""
        next_parse_nodes_list = [start_node]
        while (len(next_parse_nodes_list) > 0):
            new_child_nodes = []
            for node in next_parse_nodes_list:
                yield node
                for c in node.child:
                    new_child_nodes.append(c)
            next_parse_nodes_list = new_child_nodes
            # print("==================================")


''' =============static setting crate start================='''

def gen_vbif_lim_static_setting(file, dtsParser):
    """These are constant offset"""
    VBIF_IN_RD_LIM_CONF = [
        {'offset': 0x00B0, 'val': 0x00002020},
        {'offset': 0x00B4, 'val': 0x20202020},
        {'offset': 0x00B8, 'val': 0x20202020},
        {'offset': 0x00BC, 'val': 0x00002020}
    ]
    VBIF_IN_WR_LIM_CONF = [
        {'offset': 0x00C0, 'val': 0x00000000},
        {'offset': 0x00C4, 'val': 0x04200000},
        {'offset': 0x00C8, 'val': 0x20000000},
        {'offset': 0x00CC, 'val': 0x00000000}
    ]

    node = dtsParser.get_node_by_name("qcom,mdss_mdp")
    vbif_base, vbif_size = dtsParser.get_reg_info_by_name(node, 'reg', 'reg-names', 'vbif_phys')
    plane_xin_id = dtsParser.get_property(node, 'qcom,sde-sspp-xin-id')
    wb_xin_id = dtsParser.get_property(node, 'qcom,sde-wb-xin-id')

    def _update_ot_limit(file, conf, lim):
        conf_index = int(xin_id / 4)
        val = conf[conf_index]['val']
        bit_off = (xin_id % 4) * 8
        val &= ~(0xff << bit_off)
        val |= (lim << bit_off)
        conf[conf_index]['val'] = val
        file.write(hex(vbif_base + conf[conf_index]['offset']) + ":" + hex(val) + "\n")

    '''Config VBIF_IN_RD_LIM_CONF0~VBIF_IN_RD_LIM_CONF3'''
    vbif_default_ot_rd_limit = dtsParser.get_property(node, 'qcom,sde-vbif-default-ot-rd-limit')
    if vbif_default_ot_rd_limit is not None:
        ot_rd_limit = vbif_default_ot_rd_limit[0]
        for xin_id in plane_xin_id:
            _update_ot_limit(file, VBIF_IN_RD_LIM_CONF, ot_rd_limit)

    '''Config VBIF_IN_WR_LIM_CONF0~VBIF_IN_WR_LIM_CONF3'''
    vbif_default_ot_wr_limit = dtsParser.get_property(node, 'qcom,sde-vbif-default-ot-wr-limit')
    if vbif_default_ot_wr_limit is not None:
        ot_wr_limit = vbif_default_ot_wr_limit[0]
        for xin_id in wb_xin_id:
            _update_ot_limit(file, VBIF_IN_WR_LIM_CONF, ot_wr_limit)


def gen_vbif_memtypes_static_setting(file, dtsParser):
    """These are constant offset"""
    vbif_memtype_offset = OrderedDict()
    vbif_memtype_offset['VBIF_OUT_AXI_AMEMTYPE_CONF0'] = 0x0160
    vbif_memtype_offset['VBIF_OUT_AXI_AMEMTYPE_CONF1'] = 0x0164

    node = dtsParser.get_node_by_name("qcom,mdss_mdp")
    vbif_base, vbif_size = dtsParser.get_reg_info_by_name(node, 'reg', 'reg-names', 'vbif_phys')

    vbif_memtype0 = dtsParser.get_property(node, 'qcom,sde-vbif-memtype-0')
    vbif_memtype1 = dtsParser.get_property(node, 'qcom,sde-vbif-memtype-1')

    memtype_list = []
    for i in range(len(vbif_memtype0)):
        memtype_list.append(vbif_memtype0[i])
    for i in range(len(vbif_memtype1)):
        memtype_list.append(vbif_memtype1[i])

    memtype0_reg_val = 0
    memtype1_reg_val = 0
    for xin_id in range(len(memtype_list)):
        val = memtype_list[i]
        if xin_id < 8:
            memtype0_reg_val |= (val << (xin_id * 4))
        else:
            memtype1_reg_val |= (val << ((xin_id - 8) * 4))

    file.write(hex(vbif_base + vbif_memtype_offset['VBIF_OUT_AXI_AMEMTYPE_CONF0']) + ":" + hex(memtype0_reg_val) + "\n")
    file.write(hex(vbif_base + vbif_memtype_offset['VBIF_OUT_AXI_AMEMTYPE_CONF1']) + ":" + hex(memtype1_reg_val) + "\n")

def gen_vbif_nrt_memtypes_static_setting(file, dtsParser):
    """These are constant offset"""
    vbif_nrt_memtype_offset = OrderedDict()
    vbif_nrt_memtype_offset['VBIF_NRT_OUT_AXI_AMEMTYPE_CONF0'] = 0x0160

    node = dtsParser.get_node_by_name("qcom,mdss_rotator")
    vbif_nrt_base, vbif_nrt_size = dtsParser.get_reg_info_by_name(node, 'reg', 'reg-names', 'rot_vbif_phys')

    vbif_nrt_memtype_list = dtsParser.get_property(node, 'qcom,mdss-rot-vbif-memtype')
    if vbif_nrt_memtype_list is not None:
        memtype_reg_val = 0
        for xin_id in range(len(vbif_nrt_memtype_list)):
            val = vbif_nrt_memtype_list[xin_id]
            if xin_id >= 8:
                continue
            else:
                memtype_reg_val |= (val << ((xin_id & 0x7) * 4))

        file.write(hex(vbif_nrt_base + vbif_nrt_memtype_offset['VBIF_NRT_OUT_AXI_AMEMTYPE_CONF0']) + ":" + hex(memtype_reg_val) + "\n")


def gen_phy_setting_static_setting(file, dtsParser):
    def __gen_phy_setting_static_setting(file, dtsParser, dsi_phy_node):
        DSIPHY_LNX_CFG0 = lambda n: (0x200 + 0x80 * n)
        DSIPHY_LNX_CFG1 = lambda n: (0x204 + 0x80 * n)
        DSIPHY_LNX_CFG2 = lambda n: (0x208 + 0x80 * n)
        DSIPHY_LNX_LPRX_CTRL = lambda n: (0x214 + 0x80 * n)

        cfg_count_per_lane = 4
        strength_count_per_lane = 2
        dsi_phy_base, dsi_phy_size = dtsParser.get_reg_info_by_name(dsi_phy_node, 'reg', 'reg-names', 'dsi_phy')

        '''lanecfg'''
        lanecfg = dtsParser.get_property(dsi_phy_node, 'qcom,platform-lane-config')
        group_num = len(lanecfg) / cfg_count_per_lane
        for i in range(group_num):
            cfg = lanecfg[i * cfg_count_per_lane:(i + 1) * cfg_count_per_lane]
            cfg0_addr = dsi_phy_base + DSIPHY_LNX_CFG0(i)
            cfg0_val = cfg[0]
            cfg1_addr = dsi_phy_base + DSIPHY_LNX_CFG1(i)
            cfg1_val = cfg[1]
            cfg2_addr = dsi_phy_base + DSIPHY_LNX_CFG2(i)
            cfg2_val = cfg[2]
            file.write(hex(cfg0_addr) + ":" + hex(cfg0_val) + "\n")
            file.write(hex(cfg1_addr) + ":" + hex(cfg1_val) + "\n")
            file.write(hex(cfg2_addr) + ":" + hex(cfg2_val) + "\n")

        '''strength'''
        phy_lan0 = 0
        lanemap = dtsParser.get_property(dsi_phy_node, 'qcom,lane-map-v2')
        if lanemap is not None:
            phy_lan0 = lanemap[0]
        else:
            lanemap = dtsParser.get_property(dsi_phy_node, 'qcom,lane-map')
            if lanemap is not None:
                if lanemap[0] == "lane_map_3012":
                    phy_lan0 = 3
                if lanemap[0] == "lane_map_2301":
                    phy_lan0 = 2
                if lanemap[0] == "lane_map_1230":
                    phy_lan0 = 1
                if lanemap[0] == "lane_map_0321":
                    phy_lan0 = 0
                if lanemap[0] == "lane_map_1032":
                    phy_lan0 = 1
                if lanemap[0] == "lane_map_2103":
                    phy_lan0 = 2
                if lanemap[0] == "lane_map_3210":
                    phy_lan0 = 3

        strength = dtsParser.get_property(dsi_phy_node, 'qcom,platform-strength-ctrl')
        if strength is not None:
            _strength = strength[phy_lan0 * strength_count_per_lane: (phy_lan0 + 1) * strength_count_per_lane]
            _strength_val = _strength[1]
            lprx_ctrl_addr = dsi_phy_base + DSIPHY_LNX_LPRX_CTRL(phy_lan0)
            file.write(hex(lprx_ctrl_addr) + ":" + hex(_strength_val) + "\n")

    dsi_phy0_node = dtsParser.get_node_by_name("qcom,mdss_dsi_phy0")
    dsi_phy1_node = dtsParser.get_node_by_name("qcom,mdss_dsi_phy1")
    if dsi_phy0_node is not None:
        __gen_phy_setting_static_setting(file, dtsParser, dsi_phy0_node)
    if dsi_phy1_node is not None:
        __gen_phy_setting_static_setting(file, dtsParser, dsi_phy1_node)


''' =============static setting crate end================='''


def usage():
    print("Usage: Python DTSParse.py dtsFile")


if __name__ == '__main__':
    if len(sys.argv) < 2:
        usage()
        sys.exit(0)

    dtsParser = DTSParser(sys.argv[1])
    dtsParser.parse_all_nodes()

    '''Usage for walking through all nodes'''
    # for n in dtsParser.walk_nodes(nodes):
    #     print(n.name, node.addr)
    #     for key, val in n.property.items():
    #         print("key:", key, "val:", val)

    '''All static setting info will be appended to static_settting.txt'''
    with open("static_setting.txt", "a+") as f:
        f.truncate(0)
        """gen_vbif_lim_static_setting looks like dynamic setting, maybe this function should not be called"""
        gen_vbif_lim_static_setting(f, dtsParser)
        gen_vbif_memtypes_static_setting(f, dtsParser)
        gen_vbif_nrt_memtypes_static_setting(f, dtsParser)
        gen_phy_setting_static_setting(f, dtsParser)

    print("Create static_setting.txt successful!")
