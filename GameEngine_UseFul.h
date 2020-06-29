#ifndef GameEngine_UseFul_Include
#define GameEngine_UseFul_Include
#include "..\GameEngine_Common.h"
//--------------------------------------------------------------------------------------
// ¶¯Ì¬Êý×é
//--------------------------------------------------------------------------------------
template<typename TYPE> class CGrowableArray
{
public:
            CGrowableArray()
            {
                m_pData = NULL;
				m_nSize = 0;
				m_nMaxSize = 0;
            }
            CGrowableArray( const CGrowableArray <TYPE>& a )
            {
                for( int i = 0; i < a.m_nSize; i++ ) 
					Add( a.m_pData[i] );
            }
            ~CGrowableArray()
            {
                RemoveAll();
            }

			const TYPE& operator[]( int nIndex ) const
			{
				return GetAt( nIndex );
			}
			TYPE& operator[]( int nIndex )
			{
				return GetAt( nIndex );
			}
			CGrowableArray& operator=( const CGrowableArray <TYPE>& a )
			{
				if( this == &a ) 
					return *this; 
				RemoveAll();
				for( int i = 0; i < a.m_nSize;i++ ) 
					Add( a.m_pData[i] ); 
				return *this;
			}
			HRESULT SetSize( int nNewMaxSize );
			HRESULT Add( const TYPE& value );
			HRESULT Insert( int nIndex, const TYPE& value );
			HRESULT SetAt( int nIndex, const TYPE& value );
			TYPE& GetAt( int nIndex ) const
			{
				assert( nIndex >= 0 && nIndex < m_nSize ); 
				return m_pData[nIndex];
			}
			int     GetSize() const
			{
				return m_nSize;
			}
			TYPE* GetData()
			{
				return m_pData;
			}
			bool    Contains( const TYPE& value )
			{
				return ( -1 != IndexOf( value ) );
			}
			int     IndexOf( const TYPE& value )
			{
				return ( m_nSize > 0 ) ? IndexOf( value, 0, m_nSize ) : -1;
			}
			int     IndexOf( const TYPE& value, int iStart )
			{
				return IndexOf( value, iStart, m_nSize - iStart );
			}
			int     IndexOf( const TYPE& value, int nIndex, int nNumElements );
			int     LastIndexOf( const TYPE& value )
			{
				return ( m_nSize > 0 ) ? LastIndexOf( value, m_nSize - 1, m_nSize ) : -1;
			}
			int     LastIndexOf( const TYPE& value, int nIndex )
			{
				return LastIndexOf( value, nIndex, nIndex + 1 );
			}
			int     LastIndexOf( const TYPE& value, int nIndex, int nNumElements );

			HRESULT Remove( int nIndex );
			void    RemoveAll()
			{
				SetSize( 0 );
			}
			void    Reset()
			{
				m_nSize = 0;
			}
protected:
    TYPE* m_pData;      // the actual array of data
    int m_nSize;        // # of elements (upperBound - 1)
    int m_nMaxSize;     // max allocated

    HRESULT SetSizeInternal( int nNewMaxSize );  // This version doesn't call ctor or dtor.
};
#endif