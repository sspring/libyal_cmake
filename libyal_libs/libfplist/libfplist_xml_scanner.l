%option prefix="xml_scanner_" outfile="lex.yy.c"
%option never-interactive 8bit
%option noinput nounput noyylineno nounistd
%option noyyalloc noyyrealloc noyyfree

%{
/*
 * XML scanner functions
 *
 * Copyright (C) 2016-2018, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libfplist_libcnotify.h"
#include "libfplist_xml_parser.h"

#define YYLEX_PARAM	NULL

int xml_scanner_suppress_error   = 1;
size_t xml_scanner_buffer_offset = 0;
size_t xml_scanner_index         = 0;

#define YY_USER_ACTION	xml_scanner_buffer_offset += (size_t) xml_scanner_leng;

#if defined( HAVE_DEBUG_OUTPUT )
#define xml_scanner_token_print( string ) \
	if( libcnotify_verbose != 0 ) libcnotify_printf( "xml_scanner: offset: %" PRIzd " token: %s\n", xml_scanner_buffer_offset, string )
#else
#define xml_scanner_token_print( string )
#endif

%}

end_of_line             [\r\n|\n|\r]

name			[A-Za-z\x80-\xff_][A-Za-z\x80-\xff_0-9.-]*
escaped_value		&#([0-9]+|x[0-9a-fA-F]+);

xml_tag_content		[^<]+
xml_attribute_value	\"([^"&]|{escaped_value})*\"|\'([^'&]|{escaped_value})*\'

white_space             [\a\b\c\e\f\t\v ]+

%s XML_CONTENT
%s XML_TAG

%%

{white_space}*"<"{name} {
        xml_scanner_token_print(
         "XML_TAG_OPEN_START" );

	BEGIN( XML_TAG );

	xml_scanner_index = 0;

	while( xml_scanner_index < xml_scanner_leng )
	{
		if( xml_scanner_text[ xml_scanner_index++ ] == '<' )
		{
			break;
		}
	}
        xml_scanner_lval.string_value.data   = &( xml_scanner_text[ xml_scanner_index ] );
        xml_scanner_lval.string_value.length = (size_t) xml_scanner_leng - xml_scanner_index;

	return( XML_TAG_OPEN_START );
}

<XML_TAG>{name} {
        xml_scanner_token_print(
         "XML_ATTRIBUTE_NAME" );

        xml_scanner_lval.string_value.data   = xml_scanner_text;
        xml_scanner_lval.string_value.length = (size_t) xml_scanner_leng;

        return( XML_ATTRIBUTE_NAME );
}

<XML_TAG>"=" {
        xml_scanner_token_print(
         "XML_ATTRIBUTE_ASSIGN" );

        return( XML_ATTRIBUTE_ASSIGN );
}

<XML_TAG>{xml_attribute_value} {
        xml_scanner_token_print(
         "XML_ATTRIBUTE_VALUE" );

        xml_scanner_lval.string_value.data   = &( xml_scanner_text[ 1 ] );
        xml_scanner_lval.string_value.length = (size_t) xml_scanner_leng - 2;

        return( XML_ATTRIBUTE_VALUE );
}

<XML_TAG>"/>"{end_of_line}? {
        xml_scanner_token_print(
         "XML_TAG_END_SINGLE" );

	BEGIN( INITIAL );

        return( XML_TAG_END_SINGLE );
}

<XML_TAG>">"{end_of_line}? {
        xml_scanner_token_print(
         "XML_TAG_END" );

	BEGIN( XML_CONTENT );

        return( XML_TAG_END );
}

<XML_CONTENT>{xml_tag_content} {
        xml_scanner_token_print(
         "XML_TAG_CONTENT" );

	BEGIN( INITIAL );

        xml_scanner_lval.string_value.data   = xml_scanner_text;
        xml_scanner_lval.string_value.length = (size_t) xml_scanner_leng;

        return( XML_TAG_CONTENT );
}

"</"{name}">"{end_of_line}? {
        xml_scanner_token_print(
         "XML_TAG_CLOSE" );

	xml_scanner_index = xml_scanner_leng--;

	while( xml_scanner_index > 2 )
	{
		if( xml_scanner_text[ --xml_scanner_index ] == '>' )
		{
			break;
		}
	}
        xml_scanner_lval.string_value.data   = &( xml_scanner_text[ 2 ] );
        xml_scanner_lval.string_value.length = (size_t) xml_scanner_index - 2;

	return( XML_TAG_CLOSE );
}

<INITIAL>"<?xml"[^>]*">"{end_of_line}? {
        xml_scanner_token_print(
         "XML_PROLOGUE" );

	return( XML_PROLOGUE );
}

<INITIAL>"<!--"([^-]|"-"[^-])*"-->"{end_of_line}? {
        xml_scanner_token_print(
         "XML_COMMENT" );

	return( XML_COMMENT );
}

<INITIAL>"<!DOCTYPE"[^>]*">"{end_of_line}? {
        xml_scanner_token_print(
         "XML_DOCTYPE" );

	return( XML_DOCTYPE );
}

{end_of_line} ;

{white_space} ;

%%

void *xml_scanner_alloc(
       yy_size_t size )
{
	return( memory_allocate(
	         size ) );
}

void *xml_scanner_realloc(
       void *buffer,
       yy_size_t size )
{
	return( memory_reallocate(
	         buffer,
	         size ) );
}

void xml_scanner_free(
      void *buffer )
{
	memory_free(
	 buffer );
}

int xml_scanner_wrap(
     void )
{
	return( 1 );
}

void xml_scanner_error(
      void *parser_state,
      const char *error_string )
{
	if( xml_scanner_suppress_error == 0 )
	{
	        fprintf(
        	 stderr,
	         "%s at token: %s (offset: %" PRIzd " size: %" PRIzd ")\n",
        	 error_string,
	         xml_scanner_text,
	         xml_scanner_buffer_offset - (size_t) xml_scanner_leng,
	         (size_t) xml_scanner_leng );
	}
}

