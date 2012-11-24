#ifndef __GENERIX_LIBCPP_SINGELTON_HPP__
#define __GENERIX_LIBCPP_SINGELTON_HPP__

#ifndef __ASSEMBLER__

template <class T>
class GSingleton {
public:
	static T* Instance() {
		return &m_Obj;
	}
protected:
	GSingleton<T>(){}
	virtual ~GSingleton<T>(){}
private:

public:
protected:
private:
	static T m_Obj;
};

template <class T>
T GSingleton<T>::m_Obj;

#endif //__ASSEMBLER__

#endif //__GENERIX_LIBCPP_SINGELTON_HPP__
