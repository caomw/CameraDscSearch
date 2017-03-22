#include "lib_descriptor2sl.h"

namespace dscv2sl {

////////////////////////// Descriptor build-functions realizations
void buildDescriptorFromMat_P1_CN(const cv::Mat& mat, const recti& roi, int nBin, SDescriptorI& dsc) {
    unsigned int nch	= mat.channels();
    unsigned int sbin	= 8-nBin; //FIXME: Is it possible to make a more general approach?
    dsc.nbin	= nBin;
    dsc.type	= DSC_TYPE_1P;
    dsc.r.set(roi);
    std::map<uint64, int> tmap;
    unsigned int r0	= roi.y;
    unsigned int c0	= roi.x;
    unsigned int r1	= roi.y + roi.height;
    unsigned int c1	= roi.x + roi.width;
    uint64 tmpv;
    uint64 tmpc;
    unsigned int cnt;
    const uchar* p;
    unsigned int shiftCh;
    for(unsigned int rr=r0; rr<r1; rr++) {
        p	= mat.ptr<uchar>(rr);
        cnt = c0*nch;
        for(unsigned int cc=c0; cc<c1; cc++) {
            tmpv	= 0;
            shiftCh	= 0;
            for(unsigned int kk=0; kk<nch; kk++) {
                tmpc  = p[cnt];
                tmpv |= ((tmpc>>sbin) << shiftCh);
                cnt++;
                shiftCh += nBin;
            }
            tmap[tmpv]++;
        }
    }
    dsc.sum     = roi.height*roi.width;
    dsc.dscLen  = 1<<(nBin*nch);
    dsc.rbin    = nBin*nch;
    dsc.loadData(tmap);
}

void buildDescriptorFromMat_P2_CN(const cv::Mat& mat, const recti& roi, int nBin, SDescriptorI& dsc, unsigned int dst, bool isRotateInveriant/*=true*/) {
    unsigned int nch	= mat.channels();
    unsigned int sbin	= 8-nBin; //FIXME: Is it possible to make a more general approach?
    unsigned int pShift	= nch*nBin;
    //
    dsc.nbin	= nBin;
    dsc.type	= DSC_TYPE_2P;
    dsc.r.set(roi);
    std::map<uint64, int> tmap;
    unsigned int r0	= roi.y;
    unsigned int c0	= roi.x;
    unsigned int r1	= roi.y + roi.height;
    unsigned int c1	= roi.x + roi.width;
    uint64 tmpv1, tmpv2, tmpv;
    uint64 tmpc1, tmpc2;
    unsigned int cnt, cntN;
    const uchar* p;
    const uchar* p2;
    unsigned int shiftCh;
    const int*	dst_shift		= shift_2p[dst].data;
    const unsigned int	dst_siz	= shift_2p[dst].siz;
    unsigned int dr, dc;
    for(unsigned int rr=r0; rr<r1; rr++) {
        p	= mat.ptr<uchar>(rr);
        cnt = c0*nch;
        for(unsigned int cc=c0; cc<c1; cc++) {
            tmpv1	= 0;
            shiftCh	= 0;
            // calculate base-point
            for(unsigned int kk=0; kk<nch; kk++) {
                tmpc1  = p[cnt];
                tmpv1 |= ((tmpc1>>sbin) << shiftCh);
                cnt++;
                shiftCh += nBin;
            }
            // calculate neighbors:
            cntN = 0;
            while(cntN<dst_siz) {
                dc	= dst_shift[cntN]; //FIXME: Error! cnt -> cntN
                cntN++;
                dr	= dst_shift[cntN]; //FIXME: Error! cnt -> cntN
                cntN++;
                p2	= mat.ptr<uchar>(rr+dr, cc+dc);
                shiftCh	= 0;
                tmpv2	= 0; // !!!
                for(unsigned int kk=0; kk<nch; kk++) {
                    tmpc2  = p2[kk];
                    tmpv2 |= ((tmpc2>>sbin) << shiftCh);
                    shiftCh += nBin;
                }
                //
                if(isRotateInveriant) {
                    if(tmpv1>tmpv2) {
                        tmpv	= (tmpv1<<pShift) | tmpv2;
                    } else {
                        tmpv	= (tmpv2<<pShift) | tmpv1;
                    }
                } else {
                    tmpv	= (tmpv1<<pShift) | tmpv2;
                }
                tmap[tmpv]+=1;
            }
        }
    }
    dsc.sum     = roi.height*roi.width*dst_siz/2;
    dsc.dscLen  = 1<<(pShift*2);
    dsc.rbin    = (pShift*2);
    dsc.loadData(tmap);
}

void buildDescriptorFromMat_P3_CN(const cv::Mat& mat, const recti& roi, int nBin, SDescriptorI& dsc, unsigned int dst, bool isRotateInveriant/*=true*/) {
    unsigned int nch	= mat.channels();
    unsigned int sbin	= 8-nBin; //FIXME: Is it possible to make a more general approach?
    unsigned int pShift	= nch*nBin;
    //
    unsigned int nPnt	= 3;
    //
    dsc.nbin	= nBin;
    dsc.type	= DSC_TYPE_3P;
    dsc.r.set(roi);
    std::map<uint64, int> tmap;
    unsigned int r0	= roi.y;
    unsigned int c0	= roi.x;
    unsigned int r1	= roi.y + roi.height;
    unsigned int c1	= roi.x + roi.width;
    unsigned int tmpc, tmpv1, tmpvSum;
    unsigned int* tmpv = new unsigned int[nPnt];
    std::fill(tmpv, tmpv+nPnt, 0); // FIXME: it is really needed?
    //
    unsigned int cnt, cntN;
    const uchar* p;
    const uchar* p2;
    unsigned int shiftCh, shiftPoint;
    const int*	dst_shift		= shift_3p[dst].data;
    const unsigned int	dst_siz	= shift_3p[dst].siz;
    unsigned int dr, dc;
    for(unsigned int rr=r0; rr<r1; rr++) {
        p	= mat.ptr<uchar>(rr);
        cnt = c0*nch;
        for(unsigned int cc=c0; cc<c1; cc++) {
            tmpv[0]	= 0; //tmpv[1] = 0; tmpv[2] = 0;
            shiftCh	= 0;
            // calculate base-point
            for(unsigned int kk=0; kk<nch; kk++) {
                tmpc  = p[cnt];
                tmpv[0] |= ((tmpc>>sbin) << shiftCh);
                cnt++;
                shiftCh += nBin;
            }
            tmpv1 = tmpv[0];
            // calculate neighbors:
            cntN = 0;
            while(cntN<dst_siz) {
                tmpv[1] = 0;
                tmpv[2] = 0;
                for(unsigned int pp=1; pp<nPnt; pp++) {
                    dc	= dst_shift[cntN]; //FIXME: Error! cnt -> cntN
                    cntN++;
                    dr	= dst_shift[cntN]; //FIXME: Error! cnt -> cntN
                    cntN++;
                    p2	= mat.ptr<uchar>(rr+dr, cc+dc);
                    shiftCh	= 0;
                    for(unsigned int kk=0; kk<nch; kk++) {
                        tmpc  = p2[kk];
                        tmpv[pp] |= ((tmpc>>sbin) << shiftCh);  //FIXME: Error! tmpv[] is not cleared!, add std::fill(tmpv, tmpv+nPnt, 0)?
                        shiftCh += nBin;
                    }
                }
                //
                if(isRotateInveriant) {
                    std::sort(tmpv, tmpv+nPnt);
                }
                tmpvSum		= 0;
                shiftPoint	= 0;
                for(unsigned int tt=0; tt<nPnt; tt++) {
                    tmpvSum		|= (tmpv[tt]<<shiftPoint);
                    shiftPoint	+= pShift;
                }
                tmap[tmpvSum]++;
                //
                tmpv[0] = tmpv1;
            }
        }
    }
    dsc.sum     = roi.height*roi.width*dst_siz/(2*(nPnt-1));
    dsc.dscLen  = 1<<(pShift*nPnt);
    dsc.rbin    = pShift*nPnt;
    dsc.loadData(tmap);
}

void buildDescriptorFromMat(const cv::Mat& mat, const recti& roi, int dscType, int nBin, SDescriptorI& dsc, unsigned int dst, bool isRotateInvariant/*=true*/) {
    assert(mat.type()==CV_8UC1 || mat.type()==CV_8UC3);
    switch (dscType) {
        case DSC_TYPE_1P:
            buildDescriptorFromMat_P1_CN(mat, roi, nBin, dsc);
            break;
        case DSC_TYPE_2P:
            buildDescriptorFromMat_P2_CN(mat, roi, nBin, dsc, dst, isRotateInvariant);
            break;
        case DSC_TYPE_3P:
            buildDescriptorFromMat_P3_CN(mat, roi, nBin, dsc, dst, isRotateInvariant);
            break;
    }
}

/////////////////////////// Integral-descriptor
void integrateIMapDSC(const SDscMapI& dscIMap, const recti& roi, SDescriptorI& ret) {
    int r0	= roi.y	- dscIMap.roi.y-1;
    int c0	= roi.x	- dscIMap.roi.x-1;
    int r1	= r0 + roi.height;
    int c1	= c0 + roi.width ;
    int idx00	= r0*dscIMap.roi.width + c0;
    int idx10	= r1*dscIMap.roi.width + c0;
    int idx01	= r0*dscIMap.roi.width + c1;
    int idx11	= r1*dscIMap.roi.width + c1;
    ret.r.set(roi);
    if(r0>=0) {
        if(c0>=0) {
            ret.copyFrom(dscIMap.dataDSC[idx11]);
            ret.addBS(dscIMap.dataDSC[idx00]);
            ret.delBS_NZ(dscIMap.dataDSC[idx10]);
            ret.delBS_NZ(dscIMap.dataDSC[idx01]);
        } else {
            ret.copyFrom(dscIMap.dataDSC[idx11]);
            ret.delBS_NZ(dscIMap.dataDSC[idx01]);
        }
    } else {
        if(c0>=0) {
            ret.copyFrom(dscIMap.dataDSC[idx11]);
            ret.delBS_NZ(dscIMap.dataDSC[idx10]);
        } else {
            ret.copyFrom(dscIMap.dataDSC[idx11]);
        }
    }
    ret.type	= dscIMap.type;
    ret.r.set(roi);
}

////////////////////////////////////////////////////////////////////////////////
double SDescriptorP::getAdaptThreshMinMax(const SDescriptorP& dsc, double val) {
    uint64 kMin, kMax;
    double vMin, vMax;
    dsc.findMinMax(kMin, kMax, vMin, vMax);
    return (vMin + val*(vMax - vMin));
}

double SDescriptorP::getAdaptThreshByLen (const SDescriptorP& dsc, double val) {
    return ((double)val/(double)dsc.dscLen);
}

/////////////////////////////// Helpers to build compound-descriptors //////////
cv::Mat resizeImageProportional(const cv::Mat &img, int maxSize) {
    cv::Size siz(-1,-1);
    if(img.cols>=img.rows) {
        siz.width   = maxSize;
        siz.height  = (maxSize*img.rows)/img.cols;
    } else {
        siz.width   = (maxSize*img.cols)/img.rows;
        siz.height  = maxSize;
    }
    cv::Mat ret;
    cv::resize(img, ret, siz, 0,0, CV_INTER_CUBIC);
    return ret;
}

recti   getCorrectROIForFullImage(const cv::Mat& img, int dst) {
    return recti(dst,dst,img.cols-2*dst, img.rows-2*dst);
}

} //namespace dscv2
