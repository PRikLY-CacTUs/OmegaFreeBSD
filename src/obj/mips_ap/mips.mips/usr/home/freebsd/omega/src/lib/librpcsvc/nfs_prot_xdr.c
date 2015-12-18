/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "nfs_prot.h"
#ifndef lint
/*static char sccsid[] = "from: @(#)nfs_prot.x 1.2 87/10/12 Copyr 1987 Sun Micro";*/
/*static char sccsid[] = "from: @(#)nfs_prot.x	2.1 88/08/01 4.0 RPCSRC";*/
#endif /* not lint */
#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

bool_t
xdr_nfsstat(XDR *xdrs, nfsstat *objp)
{

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_ftype(XDR *xdrs, ftype *objp)
{

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nfs_fh(XDR *xdrs, nfs_fh *objp)
{

	if (!xdr_opaque(xdrs, objp->data, NFS_FHSIZE))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nfstime(XDR *xdrs, nfstime *objp)
{

	if (!xdr_u_int(xdrs, &objp->seconds))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->useconds))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr(XDR *xdrs, fattr *objp)
{

	if (!xdr_ftype(xdrs, &objp->type))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->mode))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->nlink))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->uid))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->gid))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->size))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->blocksize))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->rdev))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->blocks))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->fsid))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->fileid))
		return (FALSE);
	if (!xdr_nfstime(xdrs, &objp->atime))
		return (FALSE);
	if (!xdr_nfstime(xdrs, &objp->mtime))
		return (FALSE);
	if (!xdr_nfstime(xdrs, &objp->ctime))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_sattr(XDR *xdrs, sattr *objp)
{

	if (!xdr_u_int(xdrs, &objp->mode))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->uid))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->gid))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->size))
		return (FALSE);
	if (!xdr_nfstime(xdrs, &objp->atime))
		return (FALSE);
	if (!xdr_nfstime(xdrs, &objp->mtime))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_filename(XDR *xdrs, filename *objp)
{

	if (!xdr_string(xdrs, objp, NFS_MAXNAMLEN))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nfspath(XDR *xdrs, nfspath *objp)
{

	if (!xdr_string(xdrs, objp, NFS_MAXPATHLEN))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_attrstat(XDR *xdrs, attrstat *objp)
{

	if (!xdr_nfsstat(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS_OK:
		if (!xdr_fattr(xdrs, &objp->attrstat_u.attributes))
			return (FALSE);
		break;
	default:
		break;
	}
	return (TRUE);
}

bool_t
xdr_sattrargs(XDR *xdrs, sattrargs *objp)
{

	if (!xdr_nfs_fh(xdrs, &objp->file))
		return (FALSE);
	if (!xdr_sattr(xdrs, &objp->attributes))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_diropargs(XDR *xdrs, diropargs *objp)
{

	if (!xdr_nfs_fh(xdrs, &objp->dir))
		return (FALSE);
	if (!xdr_filename(xdrs, &objp->name))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_diropokres(XDR *xdrs, diropokres *objp)
{

	if (!xdr_nfs_fh(xdrs, &objp->file))
		return (FALSE);
	if (!xdr_fattr(xdrs, &objp->attributes))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_diropres(XDR *xdrs, diropres *objp)
{

	if (!xdr_nfsstat(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS_OK:
		if (!xdr_diropokres(xdrs, &objp->diropres_u.diropres))
			return (FALSE);
		break;
	default:
		break;
	}
	return (TRUE);
}

bool_t
xdr_readlinkres(XDR *xdrs, readlinkres *objp)
{

	if (!xdr_nfsstat(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS_OK:
		if (!xdr_nfspath(xdrs, &objp->readlinkres_u.data))
			return (FALSE);
		break;
	default:
		break;
	}
	return (TRUE);
}

bool_t
xdr_readargs(XDR *xdrs, readargs *objp)
{

	if (!xdr_nfs_fh(xdrs, &objp->file))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->offset))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->count))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->totalcount))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_readokres(XDR *xdrs, readokres *objp)
{

	if (!xdr_fattr(xdrs, &objp->attributes))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->data.data_val, (u_int *) &objp->data.data_len, NFS_MAXDATA))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_readres(XDR *xdrs, readres *objp)
{

	if (!xdr_nfsstat(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS_OK:
		if (!xdr_readokres(xdrs, &objp->readres_u.reply))
			return (FALSE);
		break;
	default:
		break;
	}
	return (TRUE);
}

bool_t
xdr_writeargs(XDR *xdrs, writeargs *objp)
{

	if (!xdr_nfs_fh(xdrs, &objp->file))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->beginoffset))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->offset))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->totalcount))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->data.data_val, (u_int *) &objp->data.data_len, NFS_MAXDATA))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_createargs(XDR *xdrs, createargs *objp)
{

	if (!xdr_diropargs(xdrs, &objp->where))
		return (FALSE);
	if (!xdr_sattr(xdrs, &objp->attributes))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_renameargs(XDR *xdrs, renameargs *objp)
{

	if (!xdr_diropargs(xdrs, &objp->from))
		return (FALSE);
	if (!xdr_diropargs(xdrs, &objp->to))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_linkargs(XDR *xdrs, linkargs *objp)
{

	if (!xdr_nfs_fh(xdrs, &objp->from))
		return (FALSE);
	if (!xdr_diropargs(xdrs, &objp->to))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_symlinkargs(XDR *xdrs, symlinkargs *objp)
{

	if (!xdr_diropargs(xdrs, &objp->from))
		return (FALSE);
	if (!xdr_nfspath(xdrs, &objp->to))
		return (FALSE);
	if (!xdr_sattr(xdrs, &objp->attributes))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nfscookie(XDR *xdrs, nfscookie objp)
{

	if (!xdr_opaque(xdrs, objp, NFS_COOKIESIZE))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_readdirargs(XDR *xdrs, readdirargs *objp)
{

	if (!xdr_nfs_fh(xdrs, &objp->dir))
		return (FALSE);
	if (!xdr_nfscookie(xdrs, objp->cookie))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->count))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_entry(XDR *xdrs, entry *objp)
{

	if (!xdr_u_int(xdrs, &objp->fileid))
		return (FALSE);
	if (!xdr_filename(xdrs, &objp->name))
		return (FALSE);
	if (!xdr_nfscookie(xdrs, objp->cookie))
		return (FALSE);
	{
	entry **pp = &objp->nextentry;
	if (!xdr_pointer(xdrs, (char **)pp, sizeof (entry), (xdrproc_t) xdr_entry))
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_dirlist(XDR *xdrs, dirlist *objp)
{

	{
	entry **pp = &objp->entries;
	if (!xdr_pointer(xdrs, (char **)pp, sizeof (entry), (xdrproc_t) xdr_entry))
		return (FALSE);
	}
	if (!xdr_bool(xdrs, &objp->eof))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_readdirres(XDR *xdrs, readdirres *objp)
{

	if (!xdr_nfsstat(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS_OK:
		if (!xdr_dirlist(xdrs, &objp->readdirres_u.reply))
			return (FALSE);
		break;
	default:
		break;
	}
	return (TRUE);
}

bool_t
xdr_statfsokres(XDR *xdrs, statfsokres *objp)
{

	if (!xdr_u_int(xdrs, &objp->tsize))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->bsize))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->blocks))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->bfree))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->bavail))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_statfsres(XDR *xdrs, statfsres *objp)
{

	if (!xdr_nfsstat(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS_OK:
		if (!xdr_statfsokres(xdrs, &objp->statfsres_u.reply))
			return (FALSE);
		break;
	default:
		break;
	}
	return (TRUE);
}
