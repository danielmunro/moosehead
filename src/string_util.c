/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,        *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 *                                                                         *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
 *  Chastain, Michael Quan, and Mitchell Tse.                              *
 *                                                                         *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc       *
 *  license in 'license.txt'.  In particular, you may not remove either of *
 *  these copyright notices.                                               *
 *                                                                         *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
 ***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "merc.h"
#include "db.h"
#include "log.h"

/*
 * Compare strings, case insensitive.
 * Return true if different
 *   (compatibility with historical functions).
 */
bool str_cmp( const char *astr, const char *bstr )
{
    if ( astr == NULL )
    {
  char buf[256];
  sprintf(buf, "Str_cmp: null astr. bstr: ");
  if(bstr != NULL)
    strcat(buf, bstr);
  bug( buf, 0 );
  return true;
    }

    if ( bstr == NULL )
    {
  char buf[256];
  sprintf(buf, "Str_cmp: null bstr. astr: %s", astr);
  bug( buf, 0 );
  return true;
    }

    for ( ; *astr || *bstr; astr++, bstr++ )
    {
  if ( LOWER(*astr) != LOWER(*bstr) )
      return true;
    }

    return false;
}



/*
 * Compare strings, case insensitive, for prefix matching.
 * Return true if astr not a prefix of bstr
 *   (compatibility with historical functions).
 */
bool str_prefix( const char *astr, const char *bstr )
{
    if ( astr == NULL )
    {
  bug( "Strn_cmp: null astr.", 0 );
  return true;
    }

    if ( bstr == NULL )
    {
  bug( "Strn_cmp: null bstr.", 0 );
  return true;
    }

    for ( ; *astr; astr++, bstr++ )
    {
  if ( LOWER(*astr) != LOWER(*bstr) )
      return true;
    }

    return false;
}



/*
 * Compare strings, case insensitive, for match anywhere.
 * Returns true if astr not part of bstr.
 *   (compatibility with historical functions).
 */
bool str_infix( const char *astr, const char *bstr )
{
    int sstr1;
    int sstr2;
    int ichar;
    char c0;

    if ( ( c0 = LOWER(astr[0]) ) == '\0' )
  return false;

    sstr1 = strlen(astr);
    sstr2 = strlen(bstr);

    for ( ichar = 0; ichar <= sstr2 - sstr1; ichar++ )
    {
  if ( c0 == LOWER(bstr[ichar]) && !str_prefix( astr, bstr + ichar ) )
      return false;
    }

    return true;
}



/*
 * Compare strings, case insensitive, for suffix matching.
 * Return true if astr not a suffix of bstr
 *   (compatibility with historical functions).
 */
bool str_suffix( const char *astr, const char *bstr )
{
    int sstr1;
    int sstr2;

    sstr1 = strlen(astr);
    sstr2 = strlen(bstr);
    if ( sstr1 <= sstr2 && !str_cmp( astr, bstr + sstr2 - sstr1 ) )
  return false;
    else
  return true;
}



/*
 * Returns an initial-capped string.
 */
char *capitalize( const char *str )
{
    static char strcap[MAX_STRING_LENGTH];
    int i;

    for ( i = 0; str[i] != '\0'; i++ )
  strcap[i] = LOWER(str[i]);
    strcap[i] = '\0';
    strcap[0] = UPPER(strcap[0]);
    return strcap;
}