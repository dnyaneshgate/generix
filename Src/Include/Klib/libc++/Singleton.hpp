#ifndef __GENERIX_LIBCPP_SINGELTON_HPP__
#define __GENERIX_LIBCPP_SINGELTON_HPP__

#include <Types.hpp>
#include <Macros.hpp>

template<class T>
class GSingleton {
public:

	STATIC T*
	Instance() {
		if (m_pObj == ZERO)
			m_pObj = new T();
		return m_pObj;
	}

	STATIC VOID
	Release() {
		if (m_pObj == ZERO)
			return;
		delete m_pObj;
	}

protected:

	GSingleton<T>() {
	};

	virtual ~GSingleton<T>() {
	};
private:
	STATIC T *m_pObj;
	STATIC UINT m_iCnt;
};

template <class T>
T* GSingleton<T>::m_pObj = ZERO;

template <class T>
UINT GSingleton<T>::m_iCnt = ZERO;

#endif //__GENERIX_LIBCPP_SINGELTON_HPP__
