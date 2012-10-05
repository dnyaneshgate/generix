#include <Driver.hpp>
#include <string.h>

GDriver::GDriver(UINT Id, const CHAR *Name)
{
	m_Id = Id;
	strcpy(m_Name,Name);
}

GDriver::~GDriver()
{}

CHAR*
GDriver::getName()
{
	return m_Name;
}

UINT
GDriver::getId()
{
	return m_Id;
}
