// *****************************************************************************
//  XMLFileIO   version:  1.0   Ankur Sheel  date: 2011/02/01
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef XMLFileIO_hxx__
#define XMLFileIO_hxx__

namespace Base
{
	class cString;
}

namespace Utilities
{
	class IXMLFileIO
	{
	public:
		virtual ~IXMLFileIO(){};
		////////////////////////////////////////////////////////////////////////
		/// Creates the header XML and adds the root element
		///
		/// @param[in] strRootName The name of the root element
		/// @param[in] strStyleSheetPath The stylesheet associated with this 
		/// xml. Can be NULL
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VInitializeForSave(const Base::cString & strRootName,
			const Base::cString & strStyleSheetPath) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Saves the XML file
		///
		/// @param[in] strFilePath The path for the XML file to be save
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VSave(const Base::cString & strFilePath) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Loads the XML file
		///
		/// @param[in] strFilePath The path for the XML file to be loaded
		/// @return true if the load is successfull. False otherwise
		///
		////////////////////////////////////////////////////////////////////////
		virtual bool VLoad(const Base::cString & strFilePath) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Loads the XML file. Gives the name of the root element in the XML
		///
		/// @param[in] strFilePath The path for the XML file to be loaded
		/// @param[out] strRootName the name of the root in the xml
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VLoad(const Base::cString & strFilePath,
			Base::cString & strRootName) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Parses an XML file from a character string
		///
		/// @param[in] strXML The xml string
		/// @param[in] size the size of the the string
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VParse(const Base::cString & strXML, const unsigned int size) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Adds a comment for the specified element
		///
		/// @param[in] strParentElementID The ID of the parent element
		/// @param[in] strComment The comment text
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VAddComment(const Base::cString & strParentElementID,
			const Base::cString & strComment) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Adds a element under the specified element
		///
		/// @param[in] strParentName The parent of the element
		/// @param[in] strElementAttribID The unique ID associated with the 
		/// element. Will be added as an attribute
		/// @param[in] strElementName The name of the element
		/// @param[in] strElementValue The value associated with the element
		/// @return Returns the name with which this element can be accessed
		/// 
		////////////////////////////////////////////////////////////////////////
		virtual Base::cString VAddElement(const Base::cString & strParentName, 
			const Base::cString & strElementName, const Base::cString & strElementAttribID,
			const Base::cString & strElementValue) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Adds a string attribute for the specified element
		///
		/// @param[in] strElementName The name of the element
		/// @param[in] strAttributeName The attribute name
		/// @param[in] strAttributeValue The value of the attribute
		/// 
		////////////////////////////////////////////////////////////////////////
		virtual void VAddAttribute(const Base::cString & strElementName,
			const Base::cString & strAttributeName, 
			const Base::cString & strAttributeValue) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Adds an integer attribute for the specified element
		/// 
		/// @param[in] strElementName The name of the element
		/// @param[in] strAttributeName The attribute name
		/// @param[in] iAttributeValue The integer value of the attribute
		/// 
		////////////////////////////////////////////////////////////////////////
		virtual void VAddAttribute(const Base::cString & strElementName,
			const Base::cString & strAttributeName, const int iAttributeValue) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Adds an bool attribute for the specified element
		/// 
		/// @param[in] strElementName The name of the element
		/// @param[in] strAttributeName The attribute name
		/// @param[in] bAttributeValue The boolean value of the attribute
		/// 
		////////////////////////////////////////////////////////////////////////
		virtual void VAddAttribute(const Base::cString & strElementName,
			const Base::cString & strAttributeName, const bool bAttributeValue) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Returns the string attribute value for an element attribute
		/// 
		/// @param[in] strElementID The unique ID of the element
		/// @param[in] strAttributeName The attribute name
		/// @return The value of the attribute
		/// 
		////////////////////////////////////////////////////////////////////////
		virtual Base::cString VGetNodeAttribute(const Base::cString & strElementID,
			const Base::cString & strAttributeName) const = 0;
		////////////////////////////////////////////////////////////////////////
		/// Returns the string value for an element
		///
		/// @param[in] strElementID The unique id of the element
		/// @return The value associated with the element
		///
		////////////////////////////////////////////////////////////////////////
		virtual Base::cString VGetNodeValue(const Base::cString & strElementID) const = 0;
		////////////////////////////////////////////////////////////////////////
		/// Returns the int attribute value for an element attribute
		/// 
		/// @param[in] strElementID The unique ID of the element
		/// @param[in] strAttributeName The attribute name
		/// @return The integer value of the attribute 
		///
		////////////////////////////////////////////////////////////////////////
		virtual int VGetNodeAttributeAsInt(const Base::cString & strElementID,
			const Base::cString & strAttributeName) const = 0;
		////////////////////////////////////////////////////////////////////////
		/// Returns the bool attribute value for an element attribute
		/// 
		/// @param[in] strElementID The unique ID of the element
		/// @param[in] strAttributeName The attribute name
		/// @return The bool value of the attribute 
		///
		////////////////////////////////////////////////////////////////////////
		virtual bool VGetNodeAttributeAsBool(const Base::cString & strElementID,
			const Base::cString & strAttributeName) const = 0;
		////////////////////////////////////////////////////////////////////////
		/// For a element with unique name strParentID, gets the unique names
		/// for all its children and stores it in vElements
		///
		/// @param[in] strParentID The unique id of the parent element
		/// @param[out] vElements The vector in which all the child 
		/// elements unique names are stored 
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VGetAllChildrenNames(const Base::cString & strParentID,
			std::vector<Base::cString> & vElements ) const = 0;
		////////////////////////////////////////////////////////////////////////
		/// Returns an object to use this interface
		///
		/// @return An object to use this interface
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API static IXMLFileIO * CreateXMLFile();
	};
}
#endif // XMLFileIO_h__
