/*
 * descriptor.h
 *
 *  Created on: 27.05.2012
 *      Author: ar
 */

#ifndef DESCRIPTOR2_H_
#define DESCRIPTOR2_H_

#include <iostream>
#include <fstream>
#include <sstream>

#include <algorithm>
#include <vector>
#include <map>

#include <cstdlib>
#include <cstring>
#include <cmath>

#include <cv.h>
#include <highgui.h>

#ifdef _WIN32
    typedef unsigned int uint;
#endif

namespace dscv2sl {

/////////////////////////////// Descriptor SHIFT-indexes definition ///////////////////////////////
struct stype_xp {
        unsigned int	siz;
        const int*		data;
};

#define DSC_DISTANCE_1p 0
#define DSC_DISTANCE_2p 1
#define DSC_DISTANCE_3p 2
#define DSC_DISTANCE_4p 3
#define DSC_DISTANCE_5p 4
#define DSC_DISTANCE_6p 5
#define DSC_DISTANCE_7p 6

const int dst_135[]     = {DSC_DISTANCE_1p, DSC_DISTANCE_3p, DSC_DISTANCE_5p};
const int dst_135_siz   = sizeof(dst_135)/sizeof(dst_135[0]);

//////////////// 2P-descriptor
/*
static const int mask_2p_1[8 ] = { 1,0, 1,1, -1,1, 0,1,  };
static const int mask_2p_2[14] = { 2,0, 2,1, 2,2, -2,2, -1,2, 0,2, 1,2,  };
static const int mask_2p_3[20] = { 3,0, 3,1, 3,2, 3,3, -3,3, -2,3, -1,3, 0,3, 1,3, 2,3,  };
static const int mask_2p_4[26] = { 4,0, 4,1, 4,2, 4,3, 4,4, -4,4, -3,4, -2,4, -1,4, 0,4, 1,4, 2,4, 3,4,  };
static const int mask_2p_5[32] = { 5,0, 5,1, 5,2, 5,3, 5,4, 5,5, -5,5, -4,5, -3,5, -2,5, -1,5, 0,5, 1,5, 2,5, 3,5, 4,5,  };
*/
static const int mask_2p_1[8 ] = { -1,1,  0,1,  1,0,  1,1,  };
static const int mask_2p_2[16] = { -2,1,  -2,2,  -1,2,  0,2,  1,2,  2,0,  2,1,  2,2,  };
static const int mask_2p_3[20] = { -3,1,  -3,2,  -2,3,  -1,3,  0,3,  1,3,  2,3,  3,0,  3,1,  3,2,  };
static const int mask_2p_4[24] = { -4,1,  -4,2,  -3,3,  -2,4,  -1,4,  0,4,  1,4,  2,4,  3,3,  4,0,  4,1,  4,2,  };
static const int mask_2p_5[40] = { -5,1,  -5,2,  -5,3,  -4,3,  -4,4,  -3,4,  -3,5,  -2,5,  -1,5,  0,5,  1,5,  2,5,  3,4,  3,5,  4,3,  4,4,  5,0,  5,1,  5,2,  5,3,  };
static const int mask_2p_6[36] = { -6,1,  -6,2,  -6,3,  -5,4,  -4,5,  -3,6,  -2,6,  -1,6,  0,6,  1,6,  2,6,  3,6,  4,5,  5,4,  6,0,  6,1,  6,2,  6,3,  };

#define SIZE_STYPE_2P   6

static const struct stype_xp shift_2p[SIZE_STYPE_2P] = {
        {8,  mask_2p_1},
        {14, mask_2p_2},
        {20, mask_2p_3},
        {26, mask_2p_4},
        {32, mask_2p_5},
};

//////////////// 3P-descriptor
static const int mask_3p_1[16] = {   0,1,-1,1,    1,0,0,1,     1,0,1,1,     1,1,0,1,   };
static const int mask_3p_2[16] = {   0,2,-2,1,    1,2,-1,2,    2,0,1,2,     2,1,0,2,   };
static const int mask_3p_3[16] = {  -1,3,-3,1,    1,3,-2,2,    2,2,-1,3,    3,1,1,3,   };
static const int mask_3p_4[80] = {  -2,4,-4,1,   -1,4,-4,1,   -1,4,-4,2,    0,4,-4,2,    0,4,-3,2,    1,4,-3,2,    1,4,-3,3,    2,3,-2,3,    2,3,-2,4,    2,4,-2,3,    2,4,-2,4,   3,2,-1,4,    3,2,0,4,    3,3,-1,4,   4,0,2,3,    4,0,2,4,    4,1,1,4,    4,1,2,4,    4,2,0,4,    4,2,1,4,   };
static const int mask_3p_5[32] = {  -2,5,-5,1,   -1,5,-5,2,    1,5,-4,3,    2,5,-3,4,    3,4,-2,5,    4,3,-1,5,    5,1,2,5,     5,2,1,5,   };
static const int mask_3p_6[64] = {  -2,6,-6,1,   -2,6,-6,2,   -1,6,-6,2,    0,6,-5,3,    1,6,-5,4,    2,6,-4,4,    2,6,-4,5,    3,5,-3,5,    4,4,-2,6,    4,5,-2,6,    5,3,0,6,    5,4,-1,6,    6,0,3,5,    6,1,2,6,    6,2,1,6,    6,2,2,6,   };
static const int mask_3p_7[48] = {  -2,7,-7,2,    0,7,-6,3,    0,7,-6,4,    2,7,-5,5,    3,6,-4,6,    4,6,-3,6,    5,5,-2,7,    6,3,0,7,     6,4,0,7,     7,0,3,6,     7,0,4,6,    7,2,2,7,   };

static const int mask_3p_1_f[16] = {   0,1,-1,1,     1,0,0,1,      1,0,1,1,      1,1,0,1,   };
static const int mask_3p_2_f[32] = {   0,2,-2,1,     0,2,-2,2,     1,2,-1,2,     2,0,0,2,      2,0,1,2,     2,0,2,2,     2,1,0,2,     2,2,0,2,   };
static const int mask_3p_3_f[32] = {   0,3,-3,1,     0,3,-3,2,     1,3,-2,3,     2,3,-1,3,     3,0,1,3,     3,0,2,3,     3,1,0,3,     3,2,0,3,   };
static const int mask_3p_4_f[32] = {  -1,4,-4,1,     0,4,-4,2,     1,4,-3,3,     2,4,-2,4,     3,3,-1,4,    4,0,2,4,     4,1,1,4,     4,2,0,4,   };
static const int mask_3p_5_f[80] = {  -2,5,-5,1,    -1,5,-5,1,    -1,5,-5,2,     0,5,-5,2,     0,5,-5,3,    1,5,-4,3,    1,5,-4,4,    2,5,-3,4,    2,5,-3,5,    3,4,-2,5,    3,5,-2,5,    4,3,-1,5,    4,4,-1,5,    5,0,2,5,    5,0,3,5,    5,1,1,5,    5,1,2,5,    5,2,0,5,    5,2,1,5,    5,3,0,5,   };
static const int mask_3p_6_f[48] = {  -2,6,-6,1,    -1,6,-6,2,     0,6,-6,3,     1,6,-5,4,     2,6,-4,5,    3,6,-3,6,    4,5,-2,6,    5,4,-1,6,    6,0,3,6,    6,1,2,6,    6,2,1,6,    6,3,0,6,   };
static const int mask_3p_7_f[80] = {  -3,7,-7,1,    -2,7,-7,1,    -2,7,-7,2,    -1,7,-7,2,    -1,7,-7,3,    1,7,-6,4,    1,7,-6,5,    2,7,-5,5,    2,7,-5,6,    3,7,-4,6,    4,6,-3,7,    5,5,-2,7,    5,6,-2,7,    6,4,-1,7,   6,5,-1,7,   7,1,2,7,    7,1,3,7,    7,2,1,7,    7,2,2,7,    7,3,1,7,   };

#define SIZE_STYPE_3P   7

static const struct stype_xp shift_3p[SIZE_STYPE_3P] = {
		{16,  mask_3p_1},
		{16,  mask_3p_2},
		{16,  mask_3p_3},
		{80,  mask_3p_4},
		{32,  mask_3p_5},
		{64,  mask_3p_6},
		{48,  mask_3p_7},
};

static const struct stype_xp shift_3p_f[SIZE_STYPE_3P] = {
		{16,  mask_3p_1},
		{32,  mask_3p_2},
		{32,  mask_3p_3},
		{32,  mask_3p_4},
		{80,  mask_3p_5},
		{48,  mask_3p_6},
		{80,  mask_3p_7},
};

//////////////// 9P-descriptor
static const int mask_9p_1[16] = { -1,-1,   0,-1,   1,-1,   1,0,    1,1,   0,1,  -1,1,  -1,0 };
static const int mask_9p_2[32] = { -2,-2,  -1,-2,   0,-2,   1,-2,   2,-2,  2,-1,  2,0,   2,1,   2,2,   1,2,   0,2,  -1,2,  -2,2,  -2,1,  -2,0,  -2,-1,   };
static const int mask_9p_3[48] = { -3,-3,  -2,-3,  -1,-3,   0,-3,   1,-3,  2,-3,  3,-3,  3,-2,  3,-1,  3,0,   3,1,   3,2,   3,3,   2,3,   1,3,   0,3,  -1,3,  -2,3,  -3,3,  -3,2,  -3,1,  -3,0,  -3,-1,  -3,-2,   };
static const int mask_9p_4[64] = { -4,-4,  -3,-4,  -2,-4,  -1,-4,   0,-4,  1,-4,  2,-4,  3,-4,  4,-4,  4,-3,  4,-2,  4,-1,  4,0,   4,1,   4,2,   4,3,   4,4,   3,4,   2,4,   1,4,   0,4,  -1,4,  -2,4,  -3,4,  -4,4,  -4,3,  -4,2,  -4,1,  -4,0,  -4,-1,  -4,-2,  -4,-3,   };
static const int mask_9p_5[80] = { -5,-5,  -4,-5,  -3,-5,  -2,-5,  -1,-5,  0,-5,  1,-5,  2,-5,  3,-5,  4,-5,  5,-5,  5,-4,  5,-3,  5,-2,  5,-1,  5,0,   5,1,   5,2,   5,3,   5,4,   5,5,  4,5,  3,5,  2,5,  1,5,  0,5,  -1,5,  -2,5,  -3,5,  -4,5,  -5,5,  -5,4,  -5,3,  -5,2,  -5,1,  -5,0,  -5,-1,  -5,-2,  -5,-3,  -5,-4,   };


#define SIZE_STYPE_9P   5

static const struct stype_xp shift_9p[SIZE_STYPE_9P] = {
		{16,  mask_9p_1},
		{32,  mask_9p_2},
		{48,  mask_9p_3},
		{64,  mask_9p_4},
		{80,  mask_9p_5},
};

/////////////////////////// Helper functions ///////////////////////////////
inline uint log2Int(int x) {
    uint ret = 1;
    while( x>>=1 ) ret++;
    return ret;
}

////////////////////////////////////////////////////////////////////////////
/*
 * Basic serialization interface
 */
struct IBSerializable {
    virtual void bsave(std::ofstream& fout) const = 0; // FIXME: need 'const' modificator, but Eclipse-CDT generate Bug
	virtual void bload(std::ifstream& fin ) = 0;
    virtual ~IBSerializable() {}
};

struct ICopyable {
    virtual void copyTo  (ICopyable& o) 	 const = 0; // FIXME: need 'const' modificator, but Eclipse-CDT generate Bug
	virtual void copyFrom(const ICopyable& o) = 0;
    virtual ~ICopyable() {}
};

/*
 * rectangular-area structure
 */
template <typename T>
struct rect: public IBSerializable, public ICopyable {
	T x;
	T y;
	T width;
	T height;
	rect() {
		set(0,0,0,0);
    }
	rect(T x, T y, T w, T h) {
		set(x,y,w,h);
    }
	rect(const rect<T>& r) {
		set(r);
	}
    virtual ~rect() {}
	//
	void set(const rect<T>& r) {
		set(r.x,  r.y, r.width, r.height);
	}
	void set(T x, T y, T width, T height) {
		this->x	= x;
		this->y	= y;
		this->width		= width;
		this->height	= height;
	}
	void clear() {
		set(0,0,0,0);
	}
	// serialization interface:
    virtual void bsave(std::ofstream& fout) const { // FIXME: need 'const' modificator, but Eclipse-CDT generate Bug
		fout.write((char*)&x,		sizeof(T));
		fout.write((char*)&y,		sizeof(T));
		fout.write((char*)&width,	sizeof(T));
		fout.write((char*)&height,	sizeof(T));
	}
	virtual void bload(std::ifstream& fin ) {
		fin.read((char*)&x,		sizeof(T));
		fin.read((char*)&y,		sizeof(T));
		fin.read((char*)&width,	sizeof(T));
		fin.read((char*)&height,sizeof(T));
	}
	// copyable interface:
    virtual void copyTo  (ICopyable& o) const { // FIXME: need 'const' modificator, but Eclipse-CDT generate Bug
		((rect<T>*)&o)->set(*this);
	}
	virtual void copyFrom(const ICopyable& o) {
		set(*((rect<T>*)&o));
	}
	//
	std::string toString() const {
		std::stringstream ss;
		ss << "(" << x<< ","<< y<< " " << width << "x" << height << ")";
		return ss.str();
	}
	template <typename U> friend std::ostream& operator<< (std::ostream& out, const rect<U>& r);
};

template <typename T>
std::ostream& operator<< (std::ostream& out, const rect<T>& r) {
    out << r.toString();
    return out;
}

/*
 * definition of (unsigned int)-type of rectangular area
 */
typedef rect<uint> recti;

/////////////////////////////// Sparse Descriptor

#define DSC_TYPE_UNDEF	0x0
#define DSC_TYPE_1P		0x1
#define DSC_TYPE_2P		0x2
#define DSC_TYPE_3P		0x3
#define DSC_TYPE_9P		0x9
//
#define DSC_TYPE_COMP	0x32


static const char* dsc_type_descr[] = {
		"DSC_TYPE_UNDEF",
		"DSC_TYPE_1P",
		"DSC_TYPE_2P",
		"DSC_TYPE_3P",
        "DSC_TYPE_9P",
        "DSC_TYPE_COMP"
};

/*
 * Basic sparse-descriptor structure
 */
template <typename T>
struct SDescriptor: public IBSerializable, public ICopyable {
    recti	r;
    uint	sum;
    uint	nbin;
    uint	rbin;
    uint64	dscLen;
    uint	type;
    uint	siz;
    uint64*	keys;
    T*		values;
    SDescriptor(): r(0,0,0,0), sum(0), nbin(0), rbin(0), dscLen(0), type(DSC_TYPE_UNDEF), siz(0), keys(NULL), values(NULL) {
//        std::cout << "SDescriptor::SDescriptor() [constructor]" << std::endl;
    }
    SDescriptor(const SDescriptor<T>& s): r(0,0,0,0), sum(0), nbin(0), rbin(0), dscLen(0), type(DSC_TYPE_UNDEF), siz(0), keys(NULL), values(NULL) {
		set(s);
//        std::cout << "::SDescriptor(const SDescriptor&) [copy constructor]" << std::endl;
	}
	virtual ~SDescriptor() {
//        std::cout << "SDescriptor::~SDescriptor() [destructor]" << std::endl;
		clear();
	}
	template <typename U> void setHeader(const SDescriptor<U>& s) {
		this->r.set(s.r);
		this->sum	= s.sum;
		this->nbin	= s.nbin;
        this->rbin	= s.rbin;
		this->dscLen= s.dscLen;
		this->type	= s.type;
	}
	void set(const SDescriptor<T>& s) {
		clear();
		setHeader(s);
		if((s.siz>0) && (s.keys!=NULL) && (s.values!=NULL)) {
			siz	= s.siz;
            keys	= new uint64[siz];
			values	= new T[siz];
			memcpy(keys,	s.keys,		siz*sizeof(uint));
			memcpy(values,	s.values,	siz*sizeof(T));
		}
	}
    void loadData(const std::map<uint64, T>& m) {
		clearData();
        typename std::map<uint64, T>::const_iterator it;
		siz		= m.size();
        keys	= new uint64[siz];
		values	= new T[siz];
		int cnt	= 0;
		for(it=m.begin(); it!=m.end(); it++) {
			keys  [cnt]	= it->first;
			values[cnt]	= it->second;
			cnt++;
		}
	}

	void applyThresh(T threshMin) {
		if(siz>0) {
			unsigned int newsiz = 0;
			for(unsigned int k=0; k<siz; k++) {
				if(values[k]>threshMin) {
					newsiz++;
				}
			}
			if(newsiz>0) {
				if(newsiz!=siz) {
                    uint64*	newKey	= new uint64[newsiz];
					T*		newVal	= new T[newsiz];
					int cnt	= 0;
					for(unsigned int k=0; k<siz; k++) {
						if(values[k]>threshMin) {
							newKey[cnt] = keys[k];
							newVal[cnt] = values[k];
							cnt++;
						} else {
							sum -= values[k]; // FIXME: need to debug this code-point!
						}
					}
					delete [] keys;
					delete [] values;
					siz		= newsiz;
					keys	= newKey;
					values	= newVal;
				}
			} else {
				clear(); // FIXME: may be clearData()?
			}
		}
	}

	void applyThreshInPercentToMax(T pThreshMin) {
		uint	minKey, maxKey;
		T		minVal, maxVal;
		findMinMax(minKey, maxKey, minVal, maxVal);
		T thresh	= ((pThreshMin * maxVal ) / 100);
		applyThresh(thresh);
	}

	void applyThreshInPercentToMinMax(T pThreshMinMax) {
        uint64	minKey, maxKey;
		T		minVal, maxVal;
		findMinMax(minKey, maxKey, minVal, maxVal);
		T thresh	= minVal + ((pThreshMinMax * (maxVal-minVal) ) / 100);
		applyThresh(thresh);
	}

    void findMinMax(uint64& minKey, uint64& maxKey, T& minVal, T& maxVal) const {
		if(siz>0) {
			minKey	= keys[0];
			maxKey	= keys[0];
			minVal	= values[0];
			maxVal	= values[0];
			if(siz>1) {
				for(uint i=1; i<siz; i++) {
					if(values[i]<minVal) {
						minVal	= values[i];
						minKey	= keys[i];
					} else if(values[i]>maxVal) {
						maxVal	= values[i];
						maxKey	= keys[i];
					}
				}
			}
		} else {
			minKey	= 0;
			maxKey	= 0;
			minVal	= -1;
			maxVal	= -1;
		}
	}

	void clearData() {
		if(siz>0) {
			if(keys!=NULL) {
				delete [] keys;
				keys	= NULL;
			}
			if(values!=NULL) {
				delete [] values;
				values	= NULL;
			}
		}
		siz	= 0;
	}
	void clear() {
		r.clear();
		sum		= 0;
		nbin	= 0;
        rbin	= 0;
		dscLen	= 0;
		type	= DSC_TYPE_UNDEF;
		clearData();
	}
//////////////////////
	bool isUndefined() {
		return (type == DSC_TYPE_UNDEF);
	}
//////////////////////
    virtual void bsave(std::ofstream& fout) const { // FIXME: need 'const' modificator, but Eclipse-CDT generate Bug
		r.bsave(fout);
		fout.write((char*)&sum,		sizeof(uint));
		fout.write((char*)&nbin,	sizeof(uint));
        fout.write((char*)&rbin,	sizeof(uint));
        fout.write((char*)&dscLen,	sizeof(uint64));
		fout.write((char*)&type,	sizeof(uint));
		fout.write((char*)&siz,		sizeof(uint));
        fout.write((char*)keys,		sizeof(uint64)*siz);
        fout.write((char*)values,	sizeof(T)     *siz);
	}
	virtual void bload(std::ifstream& fin ) {
		clear();
		//
		r.bload(fin);
		fin.read((char*)&sum,	sizeof(uint));
		fin.read((char*)&nbin,	sizeof(uint));
        fin.read((char*)&rbin,	sizeof(uint));
        fin.read((char*)&dscLen,sizeof(uint64));
		fin.read((char*)&type,	sizeof(uint));
		fin.read((char*)&siz,	sizeof(uint));
		//
        keys	= new uint64[siz];
		values	= new T[siz];
        fin.read((char*)keys,	sizeof(uint64)*siz);
        fin.read((char*)values,	sizeof(T)     *siz);
	}
//////////////////////
    virtual void copyTo  (ICopyable& o) const {
		((SDescriptor<T>*)&o)->set(*this);
	}
	virtual void copyFrom(const ICopyable& o) {
		set(*((SDescriptor<T>*)&o));
	}
//////////////////////
	std::string toString() const {
		std::stringstream ss;
		ss	<< "dsc { roi=" << r
            << ", sum="     << sum
            << ", nbin="    << nbin
            << ", rbin="    << rbin
            << ", dscLen="  << dscLen
            << ", type="    << type
			<< "} =" << dataToString();
		return ss.str();
	}
	std::string dataToString() const {
		std::stringstream ss;
		ss << "(" << siz << ") = [ ";
		for(unsigned int i=0; i<siz; i++) {
			ss << keys[i] << "->" << values[i] << ", ";
		}
		ss << " ]";
		return ss.str();
	}
	template <typename U> friend std::ostream& operator<< (std::ostream& out, const SDescriptor<U>&);
//////////////////////
    T L1(const SDescriptor<T>& dsc) const {
		return calc_dist_L1(*this, dsc);
	}
    T L2(const SDescriptor<T>& dsc) const {
		return calc_dist_L2(*this, dsc);
	}
	void delBS(const SDescriptor<T>& dscSmall) {
		calc_delta_BS(*this, dscSmall);
	}
	void delBS_NZ(const SDescriptor<T>& dscSmall) {
		calc_delta_BS_NZ(*this, dscSmall);
	}
	void addBS(const SDescriptor<T>& dscSmall) {
		calc_add_BS(*this, dscSmall);
	}
//////////////////////
	static T calc_dist_L1(const SDescriptor<T>& dsc1, const SDescriptor<T>& dsc2);
	static T calc_dist_L2(const SDescriptor<T>& dsc1, const SDescriptor<T>& dsc2);
	static void calc_delta_BS   (SDescriptor<T>& dscBig, const SDescriptor<T>& dscSmall);
	static void calc_delta_BS_NZ(SDescriptor<T>& dscBig, const SDescriptor<T>& dscSmall);
	static void calc_add_BS     (SDescriptor<T>& dscBig, const SDescriptor<T>& dscSmall);
////////////////////// Extended functions
	void calcSum() {
		sum	= sumValues();
	}
	T sumValues() {
		T ret = 0;
		if(siz>0 && values!=NULL) {
			for(unsigned int i=0; i<siz; i++) {
				ret	+= values[i];
			}
		}
		return ret;
	}
    void addWeightedDsc(double wDst, double wSrc, const SDescriptor<T>& src) {
        std::map<uint64, T> tmap;
        double kwDst    = wDst / (wDst + wSrc);
        double kwSrc    = wSrc / (wDst + wSrc);
        for(unsigned int ii=0; ii<siz; ii++) {
            tmap[keys[ii]] = kwDst*values[ii];
        }
        for(unsigned int ii=0; ii<src.siz; ii++) {
            tmap[src.keys[ii]] += kwSrc*src.values[ii];
        }
        loadData(tmap);
    }
    void addDsc(const SDescriptor<T>& src) {
        addWeightedDsc(1.0, 1.0, src);
    }
};

template <typename T>
void SDescriptor<T>::calc_add_BS(SDescriptor<T>& dscBig, const SDescriptor<T>& dscSmall) {
	uint n1     = dscSmall.siz;
    uint64* ks2	= dscBig.keys;
    uint64* ks1	= dscSmall.keys;
	T*	 vs2	= dscBig.values;
	T*	 vs1	= dscSmall.values;
    uint64 k1, k2;
	uint i1	= 0;
	uint i2	= 0;
	uint dSum	= 0;
	for(i1=0; i1<n1; i1++) {
		k1	= ks1[i1];
		k2	= ks2[i2];
		while(k2!=k1) {
			i2++;
			k2	= ks2[i2];
		}
		vs2[i2]	+= vs1[i1];
		dSum	+= vs1[i1];
	}
	if(dscBig.sum>0) {
		dscBig.sum	+= dSum;
	}
}

template <typename T>
void SDescriptor<T>::calc_delta_BS(SDescriptor<T>& dscBig, const SDescriptor<T>& dscSmall) {
	uint n1     = dscSmall.siz;
    uint64* ks2	= dscBig.keys;
    uint64* ks1	= dscSmall.keys;
	T*	 vs2	= dscBig.values;
	T*	 vs1	= dscSmall.values;
    uint64 k1, k2;
	uint i1	= 0;
	uint i2	= 0;
	uint dSum	= 0;
	for(i1=0; i1<n1; i1++) {
		k1	= ks1[i1];
		k2	= ks2[i2];
		while(k2!=k1) {
			i2++;
			k2	= ks2[i2];
		}
		vs2[i2]	-= vs1[i1];
		dSum	+= vs1[i1];
	}
	if(dscBig.sum>0) {
		dscBig.sum	-= dSum;
	}
}

template <typename T>
void SDescriptor<T>::calc_delta_BS_NZ(SDescriptor<T>& dscBig, const SDescriptor<T>& dscSmall) {
	uint n1     = dscSmall.siz;
    uint64* ks2	= dscBig.keys;
    uint64* ks1	= dscSmall.keys;
	T*	 vs2	= dscBig.values;
	T*	 vs1	= dscSmall.values;
    uint64 k1, k2;
	uint i1	= 0;
	uint i2	= 0;
	uint numZeros	= 0;
	uint dSum	= 0;
	for(i1=0; i1<n1; i1++) {
		k1	= ks1[i1];
		k2	= ks2[i2];
		while(k2!=k1) {
			i2++;
			k2	= ks2[i2];
		}
		vs2[i2]	-= vs1[i1];
		dSum	+= vs1[i1];
		if(vs2[i2]==0) {
			numZeros++;
		}
	}
	if(dscBig.sum>0) {
		dscBig.sum	-= dSum;
	}
	if(numZeros>0) {
		uint newSiz	= dscBig.siz - numZeros;
        uint64*	tmpK	= new uint64[newSiz];
		T*		tmpV	= new T[newSiz];
		uint cnt	= 0;
		for(uint i=0; i<dscBig.siz; i++) {
			if(vs2[i]!=0) {
				tmpK[cnt]	= ks2[i];
				tmpV[cnt]	= vs2[i];
				cnt++;
			}
		}
		delete [] dscBig.values;
		delete [] dscBig.keys;
		dscBig.keys		= tmpK;
		dscBig.values	= tmpV;
		dscBig.siz		= newSiz;
	}
}

template <typename T>
T SDescriptor<T>::calc_dist_L1(const SDescriptor<T> & dsc1, const SDescriptor<T> & dsc2) {
	uint n1     = dsc1.siz;
	uint n2     = dsc2.siz;
    uint64* ks1	= dsc1.keys;
    uint64* ks2	= dsc2.keys;
	T*	 vs1	= dsc1.values;
	T*	 vs2	= dsc2.values;
	T ret       = 0;
	T dT;
    uint64 k1, k2;
	uint i1	= 0;
	uint i2	= 0;
	while( /*(i1<n1) || (i2<n2)*/ 1) {
		if(i1==n1) {
			while(i2!=n2) {
                ret	+= fabs(vs2[i2]);
				++i2;
			}
			return ret;
		} else { k1	= ks1[i1]; }
		if(i2==n2) {
			while(i1!=n1) {
                ret	+= fabs(vs1[i1]);
				++i1;
			}
			return ret;
		} else { k2	= ks2[i2]; }
        if(k1==k2) {
            dT=vs1[i1]-vs2[i2];
            ret+=fabs(dT);
            ++i1;
            ++i2;
        } else {
            if(k1<k2) {
                dT   = vs1[i1];
                ret += fabs(dT);
                ++i1;
            } else {
                dT   = vs2[i2];
                ret += fabs(dT);
                ++i2;
            }
        }
	}
	return ret;
}

template <typename T>
T SDescriptor<T>::calc_dist_L2(const SDescriptor<T> & dsc1, const SDescriptor<T> & dsc2) {
	uint n1     = dsc1.siz;
	uint n2     = dsc2.siz;
    uint64* ks1	= dsc1.keys;
    uint64* ks2	= dsc2.keys;
	T*	 vs1	= dsc1.values;
	T*	 vs2	= dsc2.values;
	T ret       = 0;
	T dT;
    uint64 k1, k2;
	uint i1	= 0;
	uint i2	= 0;
	while( /*(i1<n1) || (i2<n2)*/ 1) {
		if(i1==n1) {
			while(i2!=n2) {
				dT	 = vs2[i2];
				ret	+= dT*dT;
				++i2;
			}
			return ret;
		} else { k1	= ks1[i1]; }
		if(i2==n2) {
			while(i1!=n1) {
				dT	 = vs1[i1];
				ret	+= dT*dT;
				++i1;
			}
			return ret;
		} else { k2	= ks2[i2]; }
        if(k1==k2) {
            dT=vs1[i1]-vs2[i2];
            ret+=dT*dT;
            ++i1;
            ++i2;
        } else {
            if(k1<k2) {
                dT   = vs1[i1];
                ret += dT*dT;
                ++i1;
            } else {
                dT   = vs2[i2];
                ret += dT*dT;
                ++i2;
            }
        }
	}
	return ret;
}


template <typename T>
std::ostream& operator<< (std::ostream& out, const SDescriptor<T>& d) {
    out << d.toString();
    return out;
}

typedef SDescriptor<int>	SDescriptorI;
typedef SDescriptor<double>	SDescriptorD;

// FIXME: not tested
struct SDescriptorP: public SDescriptor<double> {
    SDescriptorP(): SDescriptor<double>() {}
    SDescriptorP(const SDescriptorP& o): SDescriptor<double>(o) {}
	void loadFromIntDsc(const SDescriptorI& dsc) {
		clear();
		setHeader(dsc);
		if(dsc.siz>0) {
			siz	= dsc.siz;
            keys	= new uint64[siz];
			values	= new double[siz];
			for(unsigned int i=0; i<dsc.siz; i++) {
				keys[i]		= dsc.keys[i];
				values[i]	= ((double) dsc.values[i] / (double) dsc.sum );
			}
		}
		sum	= 1;
	}
	void applyThreshFloat(double thresh) {
		if(siz>0) {
			double	dsum	= 0.;
			int		newsiz	= siz;
			for(unsigned int i=0; i<siz; i++) {
				if(values[i]<thresh) {
					dsum += values[i];
					newsiz--;
				}
			}
            uint64*	newKeys	= new uint64[newsiz];
			double* newVals	= new double[newsiz];
            dsum        = 1.0-dsum;
            uint cnt    = 0;
			for(unsigned int i=0; i<siz; i++) {
				if(values[i]>=thresh) {
                    newKeys[cnt] = keys[i];
                    newVals[cnt] = values[i]/dsum;
                    cnt++;
				}
			}
			delete [] keys;
			delete [] values;
			keys	= newKeys;
			values	= newVals;
            siz = newsiz;
		}
	}
    ~SDescriptorP() {
//        std::cout << "SDescriptorP::~SDescriptorP() [destructor]" << std::endl;
    }
///////////
    double getThreshMinMax(double val) {
        return SDescriptorP::getAdaptThreshMinMax(*this, val);
    }
    double getThreshByLen (double val) {
        return SDescriptorP::getAdaptThreshByLen(*this, val);
    }
///////////
    static double getAdaptThreshMinMax(const SDescriptorP& dsc, double val);
    static double getAdaptThreshByLen (const SDescriptorP& dsc, double val);
};

////////////////////////// Descriptor build-functions definitions
void buildDescriptorFromMat(const cv::Mat& mat, const recti& roi, int dscType, int nBin, SDescriptorI& dsc, unsigned int dst=0, bool isRotateInvariant=true);
void buildDescriptorFromMat_P1_CN(const cv::Mat& mat, const recti& roi, int nBin, SDescriptorI& dsc);
void buildDescriptorFromMat_P2_CN(const cv::Mat& mat, const recti& roi, int nBin, SDescriptorI& dsc, unsigned int dst=0, bool isRotateInveriant=true);
void buildDescriptorFromMat_P3_CN(const cv::Mat& mat, const recti& roi, int nBin, SDescriptorI& dsc, unsigned int dst=0, bool isRotateInveriant=true);


//////////////////////////////////////////////////////////////
template <typename T>
struct Data2D: public IBSerializable, public ICopyable {
	uint	nrows;
	uint	ncols;
	T*		data;
    Data2D(): nrows(0), ncols(0), data(NULL) {}
	Data2D(const Data2D<T>& m) {
		set(m);
	}
	virtual ~Data2D() {
		clear();
	}
	void set(const Data2D<T>& m) {
		clear();
		uint siz	= m.size();
		nrows		= m.nrows;
		ncols		= m.ncols;
		if( (m.size()>0) && (m.data!=NULL) ) {
			data	= new T[siz];
			for(uint i=0; i<siz; i++) {
				m.data[i].copyTo(m.data[i]);
			}
		}
	}
	int size() const {
		return nrows*ncols;
	}
	void create(uint nr, uint nc) {
		clear();
		nrows	= nr;
		ncols	= nc;
		data	= new T[size()];
	}
	void clear() {
		nrows	= 0;
		ncols	= 0;
		if(data!=NULL) {
			delete [] data;
			data	= NULL;
		}
	}
/////////////////////
    virtual void bsave(std::ofstream& fout) const { // FIXME: need 'const' modificator, but Eclipse-CDT generate Bug
		fout.write((char*)&nrows,	sizeof(uint));
		fout.write((char*)&ncols,	sizeof(uint));
		int siz	= size();
		for(int i=0; i<siz; i++) {
			data[i].bsave(fout);
		}
	}
	virtual void bload(std::ifstream& fin ) {
		fin.read((char*)&nrows,	sizeof(uint));
		fin.read((char*)&ncols,	sizeof(uint));
		create(nrows, ncols);
		int siz	= size();
		for(int i=0; i<siz; i++) {
			data[i].bload(fin);
		}
	}
/////////////////////
    virtual void copyTo  (ICopyable& o) const { // FIXME: need 'const' modificator, but Eclipse-CDT generate Bug
		((Data2D<T>*)&o)->set(*this);
	}
	virtual void copyFrom(const ICopyable& o) {
		set(*((Data2D<T>*)&o));
	}
};

typedef Data2D<SDescriptorI >	MDsc2DI;
typedef Data2D<SDescriptorD >	MDsc2DD;

template <typename T>
void convertDescriptor2Vector(const SDescriptor<T>& dsc, std::vector<T>& v) {
	v.clear();
	v.resize(dsc.dscLen, 0);
	for(int i=0; i<dsc.siz; i++) {
		v[dsc.keys[i]] = dsc.values[i];
	}
}

/////////////////////////////////// Integral descriptor map ///////////////////
template <typename T>
void buildLocalDescriptorHash(uint dst_siz, const int* dst_shift, uint x, uint y, uint valueSize, uint nBin, uint nPnt, std::map<uint64, int>& lsdcm, const cv::Mat& mat) {
//	lsdcm.clear();
	unsigned int nch	= mat.channels();
	unsigned int sbin	= valueSize-nBin;
	unsigned int pShift	= nch*nBin;
	//
	uint tmpv1	= 0;
	uint tmpc	= 0;
	//
	const T* p;
	uint r0	= y;
	uint c0	= x;
	uint dr, dc;
	uint shiftCh;
	// calculate base-point
	p	= mat.ptr<T>(r0, c0);
	shiftCh	= 0;
	for(uint kk=0; kk<nch; kk++) {
		tmpc  = (uint)p[kk];
		tmpv1 |= ((tmpc>>sbin) << shiftCh);
		shiftCh += nBin;
	}
	if(nPnt>1) {
		uint tmpvSum;
		uint shiftPoint;
        uint64*	tmpv	= new uint64[nPnt];
		uint	tmpvSiz = nPnt*sizeof(uint);
		uint cntN	= 0;
		while(cntN<dst_siz) {
			memset((void*)tmpv, 0, tmpvSiz); // FIXME: it is really needed?
			tmpv[0]	= tmpv1;
			for(uint pp=1; pp<nPnt; pp++) {
				dc	= dst_shift[cntN];
				cntN++;
				dr	= dst_shift[cntN];
				cntN++;
				p	= mat.ptr<T>(r0+dr, c0+dc);
				shiftCh	= 0;
				for(uint kk=0; kk<nch; kk++) {
                    tmpc  = (uint64)p[kk];
					tmpv[pp] |= ((tmpc>>sbin) << shiftCh);
					shiftCh += nBin;
				}
			}
			std::sort(tmpv, tmpv+nPnt);	// FIXME: it is necessary only when necessary
			tmpvSum		= 0;
			shiftPoint	= 0;
			for(unsigned int tt=0; tt<nPnt; tt++) {
				tmpvSum		|= (tmpv[tt]<<shiftPoint);
				shiftPoint	+= pShift;
			}
			lsdcm[tmpvSum]++;
		}
	} else {
		lsdcm[tmpv1]++;
	}
}
//
//void buildLocalDescriptorHash_UCHAR(uint dst_siz, const int* dst_shift, uint x, uint y, uint valueSize, uint nBin, uint nPnt, std::map<uint, int>& lsdcm, const cv::Mat& mat) {
//	buildLocalDescriptorHash<uchar>(dst_siz, dst_shift, x, y, valueSize, nBin, nPnt, lsdcm, mat);
//}

///////////////////////// non-stable code /////////////////////////////
// Integrate DSC-Map: structure
template <typename T>
struct SDscIntMap: public IBSerializable, public ICopyable {
	uint	type;
	recti	roi;
    std::map<uint64, T>*	data;
	SDescriptor<T>*		dataDSC;
	//
    SDscIntMap() : type(DSC_TYPE_UNDEF), roi(0,0,0,0), data(NULL), dataDSC(NULL) {}
	virtual ~SDscIntMap() {
		clear();
	}
	void create(int r0, int c0, int nrows, int ncols) {
		clear();
		roi.set(c0, r0, ncols, nrows);
        data	= new std::map<uint64, T>[size()];
//		dataDSC	= new SDescriptor<T>[size()];
	}
	void create(const recti& roi) {
		create(roi.y, roi.x, roi.height, roi.width);
	}

	void set(const SDscIntMap<T>& o) {
		clear();
		roi.set(o.roi);
		uint siz	= size();
		if(siz>0) {
            data	= new std::map<uint64, T>[siz];
			std::copy(o.data, o.data+siz, data);
			dataDSC	= new SDescriptor<T>[siz];
			for(uint i=0; i<siz; i++) {
				o.dataDSC[i].copyTo(dataDSC[i]);
			}
		}
	}

	void clear() {
		clearData();
		clearDataDSC();
		roi.width	= 0;
		roi.height	= 0;
	}
	void clearData() {
		uint siz	= size();
		if(siz>0) {
			 if(data!=NULL) {
				 for(uint i=0; i<siz; i++) {
					 data[i].clear();
				 }
				 delete [] data;
				 data	= NULL;
			 }
		}
	}
	void clearDataDSC() {
		uint siz	= size();
		if(siz>0) {
			 if(dataDSC!=NULL) {
				 for(uint i=0; i<siz; i++) {
					 dataDSC[i].clear();
				 }
				 delete [] dataDSC;
				 dataDSC	= NULL;
			 }
		}
	}

	uint size() const {
		return roi.width*roi.height;
	}

	void convertMap2DSC() {
		clearDataDSC();
		dataDSC	= new SDescriptor<T>[size()];
		int siz	= size();
		for(int i=0; i<siz; i++) {
			dataDSC[i].loadData(data[i]);
		}
	}

	//
    virtual void bsave(std::ofstream& fout) const { // FIXME: need 'const' modificator, but Eclipse-CDT generate Bug
		fout.write((char*)&type,	sizeof(uint));
		roi.bsave(fout);
		uint siz	= size();
		if(siz>0) {
			for(uint i=0; i<siz; i++) {
				dataDSC[i].bsave(fout);
			}
		}
	}
	virtual void bload(std::ifstream& fin ) {
		clear();
		fin.read((char*)&type,	sizeof(uint));
		roi.bload(fin);
		uint siz	= size();
		dataDSC	= new SDescriptor<T>[size()];
		for(uint i=0; i<siz; i++) {
			dataDSC[i].bload(fin);
		}
	}
	//
    virtual void copyTo  (ICopyable& o) const { // FIXME: need 'const' modificator, but Eclipse-CDT generate Bug
		((SDscIntMap<T>*)&o)->set(*this);
	}
	virtual void copyFrom(const ICopyable& o) {
		set(*((SDscIntMap<T>*)&o));
	}
	/*
	template <typename U>
	void loadFromImage(const cv::Mat& image, const recti& roi, int type=DSC_TYPE_1P, int nBin=8, int dst=0, int valueSize=8) {
		loadDataFromImage<U>(image, roi, *this, type, nBin, dst, valueSize);
	}
	*/
	void integrateDSC(const recti& roi, SDescriptorI& ret) const {
		integrateIMapDSC(*this, roi, ret);
	}
//////////////////
	std::string toString() const {
		std::stringstream ss;
		ss << "idmap(" << size() << "): type=" << type << ", roi=" << roi;
		ss << ", map-data=";
		if(data!=NULL) {
			ss << "[NOT-NULL]";
		} else {
			ss << "[    NULL]";
		}
		if(dataDSC!=NULL) {
			ss << ":\n";
			ss << "\tdsc(0)=" << dataDSC[0].dataToString() << "\n...\n";
			ss << "\tdsc(" << (size()-1) << ")=" << dataDSC[size()-1].dataToString() << std::endl;
		} else {
			ss << ", DSC-data=NULL";
		}
		return ss.str();
	}
	template <typename U> friend std::ostream& operator<< (std::ostream& out, const SDscIntMap<U>&);
};

template <typename T> std::ostream& operator<< (std::ostream& out, const SDscIntMap<T>& mid) {
    out << mid.toString();
    return out;
}

typedef SDscIntMap<int>		SDscMapI;

// Integrate DSC-Map: basic external functions ::Definition
/*
template <typename T> void addMap2Map(const std::map<uint, T>& m0, std::map<uint, T>& m1);
template <typename T> void delMap2Map(const std::map<uint, T>& m0, std::map<uint, T>& m1);
template <typename T> void tetraMapSum(const std::map<uint, T>& m00, const std::map<uint, T>& m10, const std::map<uint, T>& m01, const std::map<uint, T>& m11, std::map<uint, T>& ret);
template <typename T> void loadIntDSCMapFromImage(const cv::Mat& image, const dscv2::recti& roi, SDscMapI& dscIMap, int type=DSC_TYPE_1P, int nBin=8, int dst=0, int valueSize=8);
*/
void integrateIMapDSC(const SDscMapI& dscIMap, const recti& roi, SDescriptorI& ret);

// Integrate DSC-Map: basic external functions ::Realization
template <typename T>
void addMap2Map(const std::map<uint64, T>& m0, std::map<uint64, T>& m1) {
    typename std::map<uint64, T>::const_iterator it;
    for(it=m0.begin(); it!=m0.end(); ++it) {
        m1[it->first]	+= it->second;
    }
}

template <typename T>
void delMap2Map(const std::map<uint64, T>& m0, std::map<uint64, T>& m1) {
    typename std::map<uint64, T>::const_iterator it;
    for(it=m0.begin(); it!=m0.end(); ++it) {
        m1[it->first]	-= it->second;
    }
}

template <typename T>
void tetraMapSum(const std::map<uint64, T>& m00, const std::map<uint64, T>& m10, const std::map<uint64, T>& m01, const std::map<uint64, T>& m11, std::map<uint64, T>& ret) {
    ret	= m11;
    addMap2Map(m00, ret);
    delMap2Map(m01, ret);
    delMap2Map(m10, ret);
}

template <typename T>  void loadIntDSCMapFromImage(const cv::Mat& image, const recti& roi, SDscMapI& dscIMap, int type, int nBin, int dst, int valueSize) {
    dscIMap.create(roi);
    dscIMap.type	= type;
    std::map<uint64, int> tmpm;
    int r0	= roi.y;
    int c0	= roi.x;
    int rr, cc;
    int idx, ridx;
    // check DSC-type:
    uint dst_siz	= 0;
    const int* dst_shift	= NULL;
    uint nPnt		= 1;
    switch (type) {
        case DSC_TYPE_2P:
            dst_siz		= shift_2p[dst].siz;
            dst_shift	= shift_2p[dst].data;
            nPnt		= 2;
            break;
        case DSC_TYPE_3P:
            dst_siz		= shift_3p[dst].siz;
            dst_shift	= shift_3p[dst].data;
            nPnt		= 3;
            break;
    }
    // integrate horizontal stripes
    for(uint r=0; r<roi.height; r++) {
        ridx	= r*roi.width;
        for(uint c=0; c<roi.width; c++) {
            rr	= r0 + r;
            cc	= c0 + c;
            buildLocalDescriptorHash<T>(dst_siz, dst_shift, cc, rr, valueSize, nBin, nPnt, tmpm, image);
            idx	= ridx + c;
            dscIMap.data[idx]	= tmpm;
        }
        tmpm.clear();
    }
    // integrate vertical stripes
    int idx1, idx2;
    for(uint c=0; c<roi.width; c++) {
        for(uint r=1; r<roi.height; r++) {
            idx1	= (r-1)*roi.width + c;
            idx2	= r*roi.width + c;
            addMap2Map(dscIMap.data[idx1], dscIMap.data[idx2]);
        }
    }
}


///////////////////////////////// GRID-Descriptor
template <typename T>
struct SGridDesc: public IBSerializable, public ICopyable {
	int		type;	// basic type from DSC_TYPE_*
	int		nrow;
	int		ncol;
	recti	roi;
	SDescriptor<T>* ddata;

    SGridDesc(): type(DSC_TYPE_UNDEF), nrow(0), ncol(0), roi(0,0,0,0), ddata(NULL) {}
	virtual ~SGridDesc() {
		clear();
	}
	//
	void create(int pType, int pNrow, int pNcol) {
		create(pNrow, pNcol);
		type	= pType;
	}
	void create(int pNrow, int pNcol) {
		clear();
		type	= DSC_TYPE_UNDEF;
		nrow	= pNrow;
		ncol	= pNcol;
		ddata	= new SDescriptor<T>[size()];
	}
	int size() const {
		return (nrow*ncol);
	}
	void setROI(const recti& r) {
		roi.set(r);
	}
	void clear() {
		int siz	= size();
		if(siz>0) {
			if(ddata!=NULL) {
				for(int i=0; i<siz; i++) {
					ddata[i].clear();
				}
				delete [] ddata;
			}
			roi.set(0,0,0,0);
			nrow	= 0;
			ncol	= 0;
		}
		type	= DSC_TYPE_UNDEF;
	}
	void set(const SGridDesc<T>& mdsc) {
		clear();
		type	= mdsc.type;
		roi.set(mdsc.roi);
		nrow	= mdsc.nrow;
		ncol	= mdsc.ncol;
		int siz	= mdsc.size();
		if(siz>0) {
			ddata	= new SDescriptor<T>[siz];
			for(int i=0; i<siz; i++) {
				ddata[i].copyFrom(mdsc.ddata[i]);
			}
		}
	}

	void loadDSCFromImage(const cv::Mat& img, const recti& pROI, int nBin, int dst=0) {
		roi.set(pROI);
		int dr	= roi.height / nrow;
		int dc	= roi.width  / ncol;
		recti lroi(0,0,dc,dr);
		int ridx, idx;
		int r0, c0;
		for(int rr=0; rr<nrow; rr++) {
			ridx	= ncol*rr;
			r0 		= roi.y + dr*rr;
			lroi.y	= r0;
			for(int cc=0; cc<ncol; cc++) {
				c0	= roi.x + dc*cc;
				lroi.x	= c0;
				idx	= ridx + cc;
				buildDescriptorFromMat(img, lroi, type, nBin, ddata[idx], dst);
			}
		}
	}

	void loadDSCFromIntegralDSCMap(const SDscMapI& dscIMap, const recti& pROI) {
		type	= dscIMap.type;
		roi.set(pROI);
		//
		int dr	= roi.height / nrow;
		int dc	= roi.width  / ncol;
		recti lroi(0,0,dc,dr);
		int ridx, idx;
		int r0, c0;
		for(int rr=0; rr<nrow; rr++) {
			ridx	= ncol*rr;
			r0 		= roi.y + dr*rr;
			lroi.y	= r0;
			for(int cc=0; cc<ncol; cc++) {
				c0	= roi.x + dc*cc;
				lroi.x	= c0;
				idx	= ridx + cc;
				dscIMap.integrateDSC(lroi, ddata[idx]);
			}
		}
	}

	// save/load interface:
    virtual void bsave(std::ofstream& fout) const {
		fout.write((char*)&type, sizeof(int));
		fout.write((char*)&nrow, sizeof(int));
		fout.write((char*)&ncol, sizeof(int));
		roi.bsave(fout);
		int siz	= size();
		for(int i=0; i<siz; i++) {
			ddata[i].bsave(fout);
		}
	}
	virtual void bload(std::ifstream& fin ) {
		clear();
		fin.read((char*)&type, sizeof(int));
		fin.read((char*)&nrow, sizeof(int));
		fin.read((char*)&ncol, sizeof(int));
		roi.bload(fin);
		int siz	= size();
		if(siz>0) {
			ddata	= new SDescriptor<T>[siz];
			for(int i=0; i<siz; i++) {
				ddata[i].bload(fin);
			}
		}
	}
	// copy-interface:
    virtual void copyTo  (ICopyable& o) const {
		((SGridDesc<T>*)&o)->set(*this);
	}
	virtual void copyFrom(const ICopyable& o) {
		set(*((SGridDesc<T>*)&o));
	}
	// stdout-interface:
	std::string toString() const {
		std::stringstream ss;
		ss << "type=" << type<< ", nsiz=" << ncol << "x" << nrow << ", roi=" << roi << ":\n";
		int siz	= size();
		for(int i=0; i<siz; i++) {
			ss << "\t" << ddata[i].dataToString() << std::endl;
		}
		return ss.str();
	}
	template <typename U> friend std::ostream& operator<< (std::ostream& out, const SGridDesc<U>& r);
	// measure:
	static T calc_dist_L1(const SGridDesc<T>& md1, const SGridDesc<T>& md2);
	static T calc_dist_L2(const SGridDesc<T>& md1, const SGridDesc<T>& md2);

	T L1(const SGridDesc<T>& md) {
		return calc_dist_L1(*this, md);
	}
	T L2(const SGridDesc<T>& md) {
		return calc_dist_L2(*this, md);
	}

};

template <typename T>
std::ostream& operator<< (std::ostream& out, const SGridDesc<T>& md) {
    out << md.toString();
    return out;
}

template <typename T> T SGridDesc<T>::calc_dist_L1(const SGridDesc<T>& md1, const SGridDesc<T>& md2) {
	int siz	= md1.size();
	T ret		= -1;
	if(siz==md2.size()) {
		for(int i=0; i<siz; i++) {
			ret	+= md1.ddata[i].L1(md2.ddata[i]);
		}
		ret	/= siz;
	}
	return ret;
}

template <typename T> T SGridDesc<T>::calc_dist_L2(const SGridDesc<T>& md1, const SGridDesc<T>& md2) {
	int siz	= md1.size();
	T ret		= -1;
	if(siz==md2.size()) {
		for(int i=0; i<siz; i++) {
			ret	+= md1.ddata[i].L2(md2.ddata[i]);
		}
		ret	/= siz;
	}
	return ret;
}

typedef SGridDesc<int>	GridDescI;


/////////////////////////////// Helpers to build compound-descriptors //////////
cv::Mat resizeImageProportional(const cv::Mat& img, int maxSize);
template <typename T> void buildCompoundDsc(const cv::Mat& img, const recti& roi, SDescriptor<T>& dsc, const int* dst, int numDst, int dscType, int nBin, bool isRotateInvariant/*=true*/); // FIXME: FUCKING VS2010!!!
template <typename T> void makeCompoundDsc(SDescriptor<T>& dsc, SDescriptor<T>* dscList, int numDst);
template <typename T> void buildCompoundDscGrid(const cv::Mat& img, const recti& roi, SDescriptor<T>& dsc, const int* dst, int numDst, int gridSize, int dscType, int nBin, bool isRotateInvariant/*=true*/);
template <typename T> void buildCompoundDscFullImage(const cv::Mat& img, SDescriptor<T>& dsc, const int* dst, int numDst, int dscType, int nBin, bool isRotateInvariant/*=true*/);
template <typename T> void buildCompoundDscGridFullImage(const cv::Mat& img, SDescriptor<T>& dsc, const int* dst, int numDst, int gridSize, int dscType, int nBin, bool isRotateInvariant/*=true*/);

////////////////////////
template <typename T>
void buildCompoundDscGrid(const cv::Mat& img, const recti& roi, SDescriptor<T>& dsc, const int* dst, int numDst, int gridSize, int dscType, int nBin, bool isRotateInvariant=true) {
    dsc.clear();
    int gs2 = gridSize*gridSize;
    int num = gs2*numDst;
    SDescriptor<T>* tmpDsctArray  = new SDescriptor<T>[num];
    recti groi(roi.x, roi.y, roi.width/gridSize, roi.height/gridSize);
    int cnt = 0;
    for(int x=0; x<gridSize; x++) {
//        groi.x  = roi.x + x*roi.width/gridSize;
        groi.y   = roi.y;
        for(int y=0; y<gridSize; y++) {
//            groi.y  = roi.y + y*roi.height/gridSize;
            for(int dd=0; dd<numDst; dd++) {
                buildDescriptorFromMat(img, groi, dscType, nBin, tmpDsctArray[cnt], dst[dd], isRotateInvariant);
                cnt++;
            }
            groi.y  += groi.height;
        }
        groi.x  += groi.width;
    }
    makeCompoundDsc<T>(dsc, tmpDsctArray, num);
    delete [] tmpDsctArray;
}

template <typename T>
void buildCompoundDsc(const cv::Mat& img, const recti& roi, SDescriptor<T>& dsc, const int* dst, int numDst, int dscType, int nBin, bool isRotateInvariant/*=true*/) {
    dsc.clear();
    SDescriptor<T>* tmpDsctArray  = new SDescriptor<T>[numDst];
    for(int ii=0; ii<numDst; ii++) {
        buildDescriptorFromMat(img, roi, dscType, nBin, tmpDsctArray[ii], dst[ii], isRotateInvariant);
    }
    makeCompoundDsc<T>(dsc, tmpDsctArray, numDst);
    delete [] tmpDsctArray;
}

template <typename T>
void makeCompoundDsc(SDescriptor<T>& dsc, SDescriptor<T>* dscList, int numDst) {
    dsc.clear();
    uint totSize     = 0;
    uint totSum      = 0;
    uint64 bShift    = 0;
    for(int ii=0; ii<numDst; ii++) {
        //
        if(ii>0) {
            bShift  += ((uint64)1)<<(dscList[ii-1].rbin);
            for(uint kk=0; kk<dscList[ii].siz; kk++) {
                dscList[ii].keys[kk] += bShift;
            }
        }
        totSum  += dscList[ii].sum;
        totSize += dscList[ii].siz;
    }
    //
    dsc.setHeader(dscList[0]);
    dsc.type    = DSC_TYPE_COMP;
    uint64* tmpKeys = new uint64[totSize];
    T*      tmpVals = new T[totSize];
    int shiftConcat = 0;
    for(int ii=0; ii<numDst; ii++) {
        std::copy(dscList[ii].keys,   dscList[ii].keys  +dscList[ii].siz, tmpKeys+shiftConcat);
        std::copy(dscList[ii].values, dscList[ii].values+dscList[ii].siz, tmpVals+shiftConcat);
        shiftConcat += dscList[ii].siz;
    }
    dsc.siz     = totSize;
    dsc.keys    = tmpKeys;
    dsc.values  = tmpVals;
    dsc.sum     = totSum;
    dsc.rbin    = log2Int(bShift);
    dsc.dscLen  = 1<<dsc.rbin;
}

template <typename T> void buildCompoundDscFullImage(const cv::Mat& img, SDescriptor<T>& dsc, const int* dst, int numDst, int dscType, int nBin, bool isRotateInvariant/*=true*/) {
    int maxDst  = *std::max_element(dst, dst+numDst) + 1;
    recti roi(maxDst, maxDst, img.cols-2*maxDst, img.rows-2*maxDst);
    buildCompoundDsc(img, roi, dsc, dst, numDst, dscType, nBin, isRotateInvariant);
}

template <typename T> void buildCompoundDscGridFullImage(const cv::Mat& img, SDescriptor<T>& dsc, const int* dst, int numDst, int gridSize, int dscType, int nBin, bool isRotateInvariant/*=true*/) {
    int maxDst  = *std::max_element(dst, dst+numDst) + 1;
    recti roi(maxDst, maxDst, img.cols-2*maxDst, img.rows-2*maxDst);
    buildCompoundDscGrid(img, roi, dsc, dst, numDst, gridSize, dscType, nBin, isRotateInvariant);
}

recti   getCorrectROIForFullImage(const cv::Mat& img, int dst);

} // end namespace dscv2

#endif /* DESCRIPTOR2_H_ */
