Consider the 3-byte sequence 11100000 10000000 10100001. Answer the following questions:

        *What code point does it encode in UTF-8, and what character is that?
11100000 = 0xE0
10000000 = 0x80
10100001 = 0xA1
https://www.compart.com/en/unicode/U+00A1
This is the character encoding of an inverted exclamation point.

        *What are the three other ways to encode that character?
   
 character encoding assigning a numeric value to each character, number, or symbol and let the computer intepret the data. The first way to inteperet the binary infomation would be in UTF-8 since it is a variable-length encoding system,and would be most for space efficieny considering it is a more common text than say cunciform. IN UTF-32 each character is represented by 4 bytes which makes many characters able to be represented but less efficient for other common text due to the size. In usual UTF-16 does not encode a 3-byte sequence, however certain systems can and are adjusted to handle 3-byte sequences.


        *Give an example of a character that has exactly three encodings (but not four, like the one in the previous example does)
good example of a character with exactly three distinct encodings is the letter "é" (Latin small letter E with acute, Unicode code point U+00E9). This character can appear in three different encodings across common character sets. In UTF-8 the character can be represented by 0xC3 0xA9 which is two-byte sequence encoding. In UTF-16 the representation woukd be 0x00E9 which is big-endian form, also a two-byte sequence encoding. Lastly in ISO-8859-1, the representation would be 0xE9 which is a single-byte encoding.


*What are some problems with having these multiple encodings, especially for ASCII characters? A web search for “overlong  UTF-8 encoding” may be useful here.

A problem with having mutliple encodings is that the store or tranmission capacity is wasted when used for ASCII characters. ASCII characters can be represented in multiple encodings, making storage and processing less efficient, especially in large text datasets with many ascii characters. Another problem arises when an application processes UTF-8 data from an untrusted source, and the developer assumes the encoding will always use the shortest form. For example, certain encodings might bypass SQL injection or XSS (cross-site scripting) protections if filters are not configured to recognize all possible encodings.