#include <sys/types.h>
#include <stdio.h>
#include <stdint.h>
#include <bsnmp/asn1.h>
#include <bsnmp/snmp.h>
#include <bsnmp/snmpagent.h>
#include "hostres_tree.h"

const struct snmp_node hostres_ctree[] = {
    {{ 9, { 1, 3, 6, 1, 2, 1, 25, 1, 1, }}, "hrSystemUptime", SNMP_NODE_LEAF, SNMP_SYNTAX_TIMETICKS, op_hrSystem, 0, 0, NULL, NULL },
    {{ 9, { 1, 3, 6, 1, 2, 1, 25, 1, 2, }}, "hrSystemDate", SNMP_NODE_LEAF, SNMP_SYNTAX_OCTETSTRING, op_hrSystem, 0|SNMP_NODE_CANSET, 0, NULL, NULL },
    {{ 9, { 1, 3, 6, 1, 2, 1, 25, 1, 3, }}, "hrSystemInitialLoadDevice", SNMP_NODE_LEAF, SNMP_SYNTAX_INTEGER, op_hrSystem, 0|SNMP_NODE_CANSET, 0, NULL, NULL },
    {{ 9, { 1, 3, 6, 1, 2, 1, 25, 1, 4, }}, "hrSystemInitialLoadParameters", SNMP_NODE_LEAF, SNMP_SYNTAX_OCTETSTRING, op_hrSystem, 0|SNMP_NODE_CANSET, 0, NULL, NULL },
    {{ 9, { 1, 3, 6, 1, 2, 1, 25, 1, 5, }}, "hrSystemNumUsers", SNMP_NODE_LEAF, SNMP_SYNTAX_GAUGE, op_hrSystem, 0, 0, NULL, NULL },
    {{ 9, { 1, 3, 6, 1, 2, 1, 25, 1, 6, }}, "hrSystemProcesses", SNMP_NODE_LEAF, SNMP_SYNTAX_GAUGE, op_hrSystem, 0, 0, NULL, NULL },
    {{ 9, { 1, 3, 6, 1, 2, 1, 25, 1, 7, }}, "hrSystemMaxProcesses", SNMP_NODE_LEAF, SNMP_SYNTAX_INTEGER, op_hrSystem, 0, 0, NULL, NULL },
    {{ 9, { 1, 3, 6, 1, 2, 1, 25, 2, 2, }}, "hrMemorySize", SNMP_NODE_LEAF, SNMP_SYNTAX_INTEGER, op_hrStorage, 0, 0, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 2, 3, 1, 1, }}, "hrStorageIndex", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrStorageTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 2, 3, 1, 2, }}, "hrStorageType", SNMP_NODE_COLUMN, SNMP_SYNTAX_OID, op_hrStorageTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 2, 3, 1, 3, }}, "hrStorageDescr", SNMP_NODE_COLUMN, SNMP_SYNTAX_OCTETSTRING, op_hrStorageTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 2, 3, 1, 4, }}, "hrStorageAllocationUnits", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrStorageTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 2, 3, 1, 5, }}, "hrStorageSize", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrStorageTable, 0|SNMP_NODE_CANSET, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 2, 3, 1, 6, }}, "hrStorageUsed", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrStorageTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 2, 3, 1, 7, }}, "hrStorageAllocationFailures", SNMP_NODE_COLUMN, SNMP_SYNTAX_COUNTER, op_hrStorageTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 2, 1, 1, }}, "hrDeviceIndex", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrDeviceTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 2, 1, 2, }}, "hrDeviceType", SNMP_NODE_COLUMN, SNMP_SYNTAX_OID, op_hrDeviceTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 2, 1, 3, }}, "hrDeviceDescr", SNMP_NODE_COLUMN, SNMP_SYNTAX_OCTETSTRING, op_hrDeviceTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 2, 1, 4, }}, "hrDeviceID", SNMP_NODE_COLUMN, SNMP_SYNTAX_OID, op_hrDeviceTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 2, 1, 5, }}, "hrDeviceStatus", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrDeviceTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 2, 1, 6, }}, "hrDeviceErrors", SNMP_NODE_COLUMN, SNMP_SYNTAX_COUNTER, op_hrDeviceTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 3, 1, 1, }}, "hrProcessorFrwID", SNMP_NODE_COLUMN, SNMP_SYNTAX_OID, op_hrProcessorTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 3, 1, 2, }}, "hrProcessorLoad", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrProcessorTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 4, 1, 1, }}, "hrNetworkIfIndex", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrNetworkTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 5, 1, 1, }}, "hrPrinterStatus", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrPrinterTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 5, 1, 2, }}, "hrPrinterDetectedErrorState", SNMP_NODE_COLUMN, SNMP_SYNTAX_OCTETSTRING, op_hrPrinterTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 6, 1, 1, }}, "hrDiskStorageAccess", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrDiskStorageTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 6, 1, 2, }}, "hrDiskStorageMedia", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrDiskStorageTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 6, 1, 3, }}, "hrDiskStorageRemovable", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrDiskStorageTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 6, 1, 4, }}, "hrDiskStorageCapacity", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrDiskStorageTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 7, 1, 1, }}, "hrPartitionIndex", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrPartitionTable, 0, 0x112, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 7, 1, 2, }}, "hrPartitionLabel", SNMP_NODE_COLUMN, SNMP_SYNTAX_OCTETSTRING, op_hrPartitionTable, 0, 0x112, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 7, 1, 3, }}, "hrPartitionID", SNMP_NODE_COLUMN, SNMP_SYNTAX_OCTETSTRING, op_hrPartitionTable, 0, 0x112, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 7, 1, 4, }}, "hrPartitionSize", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrPartitionTable, 0, 0x112, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 7, 1, 5, }}, "hrPartitionFSIndex", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrPartitionTable, 0, 0x112, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 8, 1, 1, }}, "hrFSIndex", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrFSTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 8, 1, 2, }}, "hrFSMountPoint", SNMP_NODE_COLUMN, SNMP_SYNTAX_OCTETSTRING, op_hrFSTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 8, 1, 3, }}, "hrFSRemoteMountPoint", SNMP_NODE_COLUMN, SNMP_SYNTAX_OCTETSTRING, op_hrFSTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 8, 1, 4, }}, "hrFSType", SNMP_NODE_COLUMN, SNMP_SYNTAX_OID, op_hrFSTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 8, 1, 5, }}, "hrFSAccess", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrFSTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 8, 1, 6, }}, "hrFSBootable", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrFSTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 8, 1, 7, }}, "hrFSStorageIndex", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrFSTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 8, 1, 8, }}, "hrFSLastFullBackupDate", SNMP_NODE_COLUMN, SNMP_SYNTAX_OCTETSTRING, op_hrFSTable, 0|SNMP_NODE_CANSET, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 3, 8, 1, 9, }}, "hrFSLastPartialBackupDate", SNMP_NODE_COLUMN, SNMP_SYNTAX_OCTETSTRING, op_hrFSTable, 0|SNMP_NODE_CANSET, 0x11, NULL, NULL },
    {{ 9, { 1, 3, 6, 1, 2, 1, 25, 4, 1, }}, "hrSWOSIndex", SNMP_NODE_LEAF, SNMP_SYNTAX_INTEGER, op_hrSWRun, 0, 0, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 4, 2, 1, 1, }}, "hrSWRunIndex", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrSWRunTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 4, 2, 1, 2, }}, "hrSWRunName", SNMP_NODE_COLUMN, SNMP_SYNTAX_OCTETSTRING, op_hrSWRunTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 4, 2, 1, 3, }}, "hrSWRunID", SNMP_NODE_COLUMN, SNMP_SYNTAX_OID, op_hrSWRunTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 4, 2, 1, 4, }}, "hrSWRunPath", SNMP_NODE_COLUMN, SNMP_SYNTAX_OCTETSTRING, op_hrSWRunTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 4, 2, 1, 5, }}, "hrSWRunParameters", SNMP_NODE_COLUMN, SNMP_SYNTAX_OCTETSTRING, op_hrSWRunTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 4, 2, 1, 6, }}, "hrSWRunType", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrSWRunTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 4, 2, 1, 7, }}, "hrSWRunStatus", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrSWRunTable, 0|SNMP_NODE_CANSET, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 5, 1, 1, 1, }}, "hrSWRunPerfCPU", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrSWRunPerfTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 5, 1, 1, 2, }}, "hrSWRunPerfMem", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrSWRunPerfTable, 0, 0x11, NULL, NULL },
    {{ 9, { 1, 3, 6, 1, 2, 1, 25, 6, 1, }}, "hrSWInstalledLastChange", SNMP_NODE_LEAF, SNMP_SYNTAX_TIMETICKS, op_hrSWInstalled, 0, 0, NULL, NULL },
    {{ 9, { 1, 3, 6, 1, 2, 1, 25, 6, 2, }}, "hrSWInstalledLastUpdateTime", SNMP_NODE_LEAF, SNMP_SYNTAX_TIMETICKS, op_hrSWInstalled, 0, 0, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 6, 3, 1, 1, }}, "hrSWInstalledIndex", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrSWInstalledTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 6, 3, 1, 2, }}, "hrSWInstalledName", SNMP_NODE_COLUMN, SNMP_SYNTAX_OCTETSTRING, op_hrSWInstalledTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 6, 3, 1, 3, }}, "hrSWInstalledID", SNMP_NODE_COLUMN, SNMP_SYNTAX_OID, op_hrSWInstalledTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 6, 3, 1, 4, }}, "hrSWInstalledType", SNMP_NODE_COLUMN, SNMP_SYNTAX_INTEGER, op_hrSWInstalledTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 2, 1, 25, 6, 3, 1, 5, }}, "hrSWInstalledDate", SNMP_NODE_COLUMN, SNMP_SYNTAX_OCTETSTRING, op_hrSWInstalledTable, 0, 0x11, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 4, 1, 12325, 1, 202, 1, 1, }}, "begemotHrStorageUpdate", SNMP_NODE_LEAF, SNMP_SYNTAX_TIMETICKS, op_begemot, 0|SNMP_NODE_CANSET, 0, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 4, 1, 12325, 1, 202, 1, 2, }}, "begemotHrFSUpdate", SNMP_NODE_LEAF, SNMP_SYNTAX_TIMETICKS, op_begemot, 0|SNMP_NODE_CANSET, 0, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 4, 1, 12325, 1, 202, 1, 3, }}, "begemotHrDiskStorageUpdate", SNMP_NODE_LEAF, SNMP_SYNTAX_TIMETICKS, op_begemot, 0|SNMP_NODE_CANSET, 0, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 4, 1, 12325, 1, 202, 1, 4, }}, "begemotHrNetworkUpdate", SNMP_NODE_LEAF, SNMP_SYNTAX_TIMETICKS, op_begemot, 0|SNMP_NODE_CANSET, 0, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 4, 1, 12325, 1, 202, 1, 5, }}, "begemotHrSWInstalledUpdate", SNMP_NODE_LEAF, SNMP_SYNTAX_TIMETICKS, op_begemot, 0|SNMP_NODE_CANSET, 0, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 4, 1, 12325, 1, 202, 1, 6, }}, "begemotHrSWRunUpdate", SNMP_NODE_LEAF, SNMP_SYNTAX_TIMETICKS, op_begemot, 0|SNMP_NODE_CANSET, 0, NULL, NULL },
    {{ 11, { 1, 3, 6, 1, 4, 1, 12325, 1, 202, 1, 7, }}, "begemotHrPkgDir", SNMP_NODE_LEAF, SNMP_SYNTAX_OCTETSTRING, op_begemot, 0|SNMP_NODE_CANSET, 0, NULL, NULL },
};

