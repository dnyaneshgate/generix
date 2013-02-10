#include "FileSystemInterface.hpp"
#include <string.h>

namespace Generix {

fs_node::fs_node(CONST CHAR *Name) :
		m_uc_Type(FILE_TYPE_REGULAR), m_us_Permissions(ZERO), m_ui_NoOfChilds(
				ZERO), m_p_Next(ZERO), m_p_Prev(ZERO), m_p_Parent(ZERO), m_p_Child(
				ZERO) {
	memset(m_c_Name, ZERO, SIZEOF(m_c_Name));
	strcpy(m_c_Name, Name);
}

fs_node::fs_node(CONST CHAR *Name, UCHAR Type, USHORT Permissions) :
		m_uc_Type(Type), m_us_Permissions(Permissions), m_ui_NoOfChilds(ZERO), m_p_Next(
				ZERO), m_p_Prev(ZERO), m_p_Parent(ZERO), m_p_Child(ZERO) {
	memset(m_c_Name, ZERO, SIZEOF(m_c_Name));
	strcpy(m_c_Name, Name);
}

fs_node::fs_node(CONST CHAR *Name, UCHAR Type, USHORT Permissions,
		fs_node *Parent) :
		m_uc_Type(Type), m_us_Permissions(Permissions), m_ui_NoOfChilds(ZERO), m_p_Next(
				ZERO), m_p_Prev(ZERO), m_p_Parent(Parent), m_p_Child(ZERO) {
	memset(m_c_Name, ZERO, SIZEOF(m_c_Name));
	strcpy(m_c_Name, Name);
}

fs_node::~fs_node() {
	m_p_Parent = ZERO;
	m_p_Child = ZERO;
}

BOOL fs_node::AddChild(fs_node *child) {
	if (m_uc_Type != FILE_TYPE_DIRECTORY)
		return FALSE;

	if (m_p_Child == ZERO) {
		m_p_Child = child;
		child->m_p_Next = ZERO;
		child->m_p_Parent = this;
		child->m_p_Prev = ZERO;
		return TRUE;
	} else {
		fs_node *fs_node_ptr = m_p_Child;
		while (fs_node_ptr->Next())
			fs_node_ptr = fs_node_ptr->Next();
		fs_node_ptr->m_p_Next = child;
		child->m_p_Next = ZERO;
		child->m_p_Parent = this;
		child->m_p_Prev = ZERO;
		return TRUE;
	}
	return FALSE;
}

BOOL fs_node::DelChild(fs_node *child) {
	if (m_uc_Type != FILE_TYPE_DIRECTORY)
		return FALSE;

	if (m_p_Child == ZERO)
		return FALSE;

	fs_node *fs_node_ptr = m_p_Child;
	while (fs_node_ptr != child && fs_node_ptr)
		fs_node_ptr = fs_node_ptr->Next();

	if (fs_node_ptr == ZERO)
		return FALSE;
	if (fs_node_ptr == m_p_Child) {
		m_p_Child = m_p_Child->Next();
		m_p_Child->m_p_Prev = ZERO;
	} else {
		fs_node *prev = fs_node_ptr->Prev();
		fs_node *next = fs_node_ptr->Next();

		if (prev) {
			prev->m_p_Next = next;
		}
		if (next) {
			next->m_p_Prev = prev;
		}
	}

	return TRUE;
}

BOOL fs_node::Destroy() {
	return FALSE;
}

fs_node *fs_node::Next() {
	return m_p_Next;
}

fs_node *fs_node::Prev() {
	return m_p_Prev;
}

fs_node *fs_node::Parent() {
	return m_p_Parent;
}

fs_node *fs_node::Child() {
	return m_p_Child;
}

CONST CHAR* fs_node::Name() {
	return (CONST CHAR*) m_c_Name;
}

USHORT fs_node::Permissions() {
	return m_us_Permissions;
}

UINT fs_node::TotalChilds() {
	return m_ui_NoOfChilds;
}

}
