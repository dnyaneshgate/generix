/* 
 * File:   FileSystemInterface.hpp
 * Author: dnyaneshg
 *
 * Created on January 28, 2013, 10:20 PM
 */

#ifndef __GENERIX_FILESYSTEM_FILESYSTEMINTERFACE_HPP__
#define	__GENERIX_FILESYSTEM_FILESYSTEMINTERFACE_HPP__

#include <Types.hpp>
#include <Macros.hpp>

#define MAX_NAME_SIZE 128
#define FILE_TYPE_REGULAR 1
#define FILE_TYPE_DIRECTORY 2

namespace Generix {

	class fs_node {
		//member functions
	public:
		fs_node(CONST CHAR *Name);
		fs_node(CONST CHAR *Name, UCHAR Type, USHORT Permissions);
		fs_node(CONST CHAR *Name, UCHAR Type, USHORT Permissions, fs_node *Parent);
		~fs_node();
		BOOL AddChild(fs_node *child);
		BOOL DelChild(fs_node *child);
		BOOL Destroy();
		fs_node *Next();
		fs_node *Prev();
		fs_node *Parent();
		fs_node *Child();
		CONST CHAR* Name();
		USHORT Permissions();
		UINT   TotalChilds();
	protected:
	private:

		//member variables
	public:
	protected:
	private:
		CHAR m_c_Name[MAX_NAME_SIZE];
		UCHAR m_uc_Type;
		USHORT m_us_Permissions;
		UINT m_ui_NoOfChilds;
		fs_node *m_p_Next, *m_p_Prev, *m_p_Parent, *m_p_Child;
	};

}

#endif	/* __GENERIX_FILESYSTEM_FILESYSTEMINTERFACE_HPP__ */

