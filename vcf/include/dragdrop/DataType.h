/* Generated by Together */


#ifndef DATATYPE_H
#define DATATYPE_H

namespace VCF{

class ClipboardDataObject;

#define  BASIC_DATA_TYPE			100
#define  STRING_DATA_TYPE			BASIC_DATA_TYPE + 1
#define	 INTEGER_DATA_TYPE			BASIC_DATA_TYPE + 2
#define	 OBJECT_DATA_TYPE			BASIC_DATA_TYPE + 3
#define	 FILE_DATA_TYPE				BASIC_DATA_TYPE + 4
#define	 BYTE_STREAM_DATA_TYPE		BASIC_DATA_TYPE + 5
#define	 IMAGE_DATA_TYPE			BASIC_DATA_TYPE + 6
#define	 COMPONENT_DATA_TYPE		BASIC_DATA_TYPE + 7

#define  CUSTOM_DATA_TYPE			BASIC_DATA_TYPE + 100


class APPKIT_API DataType : public Object {

public:    

    DataType( const unsigned long & rawType );


    String getMimeEncodedInfo();

    unsigned long getRawType();

private:    
    unsigned long m_rawType;
};

};
#endif //DATATYPE_H