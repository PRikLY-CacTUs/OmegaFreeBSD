/*
 * Automatically generated by:
 * $FreeBSD$
 */
#include <sys/param.h>
#include <sys/errno.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/linker.h>
#include <sys/firmware.h>
#include <sys/systm.h>

static long realtek_license_ack = 0;
extern char _binary_urtwn_rtl8192cfwU_fw_start[], _binary_urtwn_rtl8192cfwU_fw_end[];

static int
urtwn_rtl8192cfwU_fw_modevent(module_t mod, int type, void *unused)
{
	const struct firmware *fp, *parent;
	int error;
	switch (type) {
	case MOD_LOAD:


		TUNABLE_LONG_FETCH("legal.realtek.license_ack", &realtek_license_ack);
		if (!realtek_license_ack) {
			printf("urtwn-rtl8192cfwU: You need to read the LICENSE file in /usr/share/doc/legal/realtek.LICENSE.\n");
			printf("urtwn-rtl8192cfwU: If you agree with the license, set legal.realtek.license_ack=1 in /boot/loader.conf.\n");
			return(EPERM);
		}

		fp = firmware_register("urtwn-rtl8192cfwU", _binary_urtwn_rtl8192cfwU_fw_start , (size_t)(_binary_urtwn_rtl8192cfwU_fw_end - _binary_urtwn_rtl8192cfwU_fw_start), 111, NULL);
		if (fp == NULL)
			goto fail_0;
		parent = fp;
		return (0);
	fail_0:
		return (ENXIO);
	case MOD_UNLOAD:
		error = firmware_unregister("urtwn-rtl8192cfwU");
		return (error);
	}
	return (EINVAL);
}

static moduledata_t urtwn_rtl8192cfwU_fw_mod = {
        "urtwn_rtl8192cfwU_fw",
        urtwn_rtl8192cfwU_fw_modevent,
        0
};
DECLARE_MODULE(urtwn_rtl8192cfwU_fw, urtwn_rtl8192cfwU_fw_mod, SI_SUB_DRIVERS, SI_ORDER_FIRST);
MODULE_VERSION(urtwn_rtl8192cfwU_fw, 1);
MODULE_DEPEND(urtwn_rtl8192cfwU_fw, firmware, 1, 1, 1);

