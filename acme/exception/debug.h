#pragma once


CLASS_DECL_ACME int __node_is_debugger_attached();

CLASS_DECL_ACME int is_debugger_attached();


CLASS_DECL_ACME bool EnforceFilter( bool bEnforce );

// WriteMemory function
//
// This function writes the specified sequence of bytes from
// the source memory into the target memory. In addition, the function
// modifies virtual memory protection attributes of the target memory page
// to make sure that it is writeable.
//
CLASS_DECL_ACME bool WriteMemory( byte* pTarget, const byte* pSource, u32 size );



