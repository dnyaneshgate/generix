#ifndef __GENERIX_LIBCPP_SINGELTON_HPP__
#define __GENERIX_LIBCPP_SINGELTON_HPP__

#ifndef __ASSEMBLER__

template <class T>
class GSingleton {
public:
	static T* Instance() {
		return &Obj;
	}
protected:
	GSingleton<T>(){}
	~GSingleton<T>(){}
private:

public:
protected:
private:
	static T Obj;
};

template <class T> T GSingleton<T>::Obj;

#endif //__ASSEMBLER__

#endif //__GENERIX_LIBCPP_SINGELTON_HPP__
