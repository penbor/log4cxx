/***************************************************************************
                          patternlayout.h  -  class PatternLayout
                             -------------------
    begin                : dim avr 20 2003
    copyright            : (C) 2003 by Michael CATANZARITI
    email                : mcatan@free.fr
 ***************************************************************************/

/***************************************************************************
 * Copyright (C) The Apache Software Foundation. All rights reserved.      *
 *                                                                         *
 * This software is published under the terms of the Apache Software       *
 * License version 1.1, a copy of which has been included with this        *
 * distribution in the LICENSE.txt file.                                   *
 ***************************************************************************/

#ifndef _LOG4CXX_PATTERN_LAYOUT_H
#define _LOG4CXX_PATTERN_LAYOUT_H

#include <log4cxx/layout.h>

namespace log4cxx
{
	namespace helpers
	{
		class PatternConverter;
		typedef ObjectPtr<PatternConverter> PatternConverterPtr;
	};

	/**

	A flexible layout configurable with pattern string.

	<p>The goal of this class is to #format a {@link
	spi::LoggingEvent LoggingEvent} and return the results as a string. 
	The results depend on the <em>conversion pattern</em>.

	<p>The conversion pattern is closely related to the conversion
	pattern of the printf function in C. A conversion pattern is
	composed of literal text and format control expressions called
	<em>conversion specifiers</em>.

	<p><i>You are free to insert any literal text within the conversion
	pattern.</i>

	<p>Each conversion specifier starts with a percent sign (\%) and is
	followed by optional <em>format modifiers</em> and a <em>conversion
	character</em>. The conversion character specifies the type of
	data, e.g. logger, priority, date, thread name. The format
	modifiers control such things as field width, padding, left and
	right justification. The following is a simple example.

	<p>Let the conversion pattern be <b>"\%-5p [\%t]: \%m\%n"</b> and assume
	that the log4cxx environment was set to use a PatternLayout. Then the
	statements
	<pre>
	LoggerPtr root = Logger::getRoot();
	root->debug("Message 1");
	root->warn("Message 2");
	</pre>
	would yield the output
	<pre>
	DEBUG [main]: Message 1
	WARN  [main]: Message 2
	</pre>

	<p>Note that there is no explicit separator between text and
	conversion specifiers. The pattern parser knows when it has reached
	the end of a conversion specifier when it reads a conversion
	character. In the example above the conversion specifier
	<b>\%-5p</b> means the priority of the logging event should be left
	justified to a width of five characters.

	The recognized conversion characters are

	<p>
	<table border="1" CELLPADDING="8">
	<tr>
	<td align=center><b>Conversion Character</b></td>
	<td align=center><b>Effect</b></td>
	</tr>

	<tr>
	<td align=center><b>c</b></td>

	<td>Used to output the logger of the logging event. The
	logger conversion specifier can be optionally followed by
	<em>precision specifier</em>, that is a decimal constant in
	brackets.

	<p>If a precision specifier is given, then only the corresponding
	number of right most components of the logger name will be
	printed. By default the logger name is printed in full.

	<p>For example, for the logger name "a.b.c" the pattern
	<b>\%c{2}</b> will output "b.c".

	</td>
	</tr>

	<tr> <td align=center><b>d</b></td> <td>Used to output the date of
	the logging event. The date conversion specifier may be
	followed by a <em>date format specifier</em> enclosed between
	braces. For example, <b>\%d{\%H:\%M:\%s}</b> or
	<b>\%d{\%d&nbsp;\%b&nbsp;\%Y&nbsp;\%H:\%M:\%s}</b>.  If no
	date format specifier is given then {@link helpers::ISO8601DateFormat
	ISO8601 format} is assumed.

	<p>The Following format options are possible:
	<li>%a -- Abbreviated weekday name
	<li>%A -- Full weekday name
	<li>%b -- Abbreviated month name
	<li>%B -- Full month name
	<li>%c -- Standard date and time string
	<li>%d -- Day of month as a decimal(1-31)
	<li>%H -- Hour(0-23)
	<li>%I -- Hour(1-12)
	<li>%j -- Day of year as a decimal(1-366)
	<li>%m -- Month as decimal(1-12)
	<li>%M -- Minute as decimal(0-59)
	<li>%p -- Locale's equivalent of AM or PM
	<li>%S -- Second as decimal(0-59)
	<li>%U -- Week of year, Sunday being first day(0-53)
	<li>%w -- Weekday as a decimal(0-6, Sunday being 0)
	<li>%W -- Week of year, Monday being first day(0-53)
	<li>%x -- Standard date string
	<li>%X -- Standard time string
	<li>%y -- Year in decimal without century(0-99)
	<li>%Y -- Year including century as decimal
	<li>%Z -- Time zone name
	<li>%% -- The percent sign

	<p>Lookup the documentation for the <code>strftime()</code> function
	found in the <code>&lt;ctime&gt;</code> header for more information.

	<p>You can alos use the log4cxx predefined date
	formatters. These can be specified using one of the strings
	"ABSOLUTE", "DATE" and "ISO8601" for specifying {@link
	helpers::AbsoluteTimeDateFormat
	AbsoluteTimeDateFormat}, {@link
	helpers::DateTimeDateFormat DateTimeDateFormat}
	and respectively {@link
	helpers::ISO8601DateFormat
	ISO8601DateFormat}. For example, <b>\%d{ISO8601}</b> or
	<b>\%d{ABSOLUTE}</b>.

	</td>
	</tr>

	<tr>
	<td align=center><b>F</b></td>

	<td>Used to output the file name where the logging request was
	issued.

	<p><b>WARNING</b> Generating caller location information is
	extremely slow. It's use should be avoided unless execution speed
	is not an issue.

	</tr>

	<tr>
	<td align=center><b>l</b></td>

	<td>Used to output location information of the caller which generated
	the logging event.

	<p>The location information can be very useful. However, it's
	generation is <em>extremely</em> slow. It's use should be avoided
	unless execution speed is not an issue.

	</td>
	</tr>

	<tr>
	<td align=center><b>L</b></td>

	<td>Used to output the line number from where the logging request
	was issued.

	<p><b>WARNING</b> Generating caller location information is
	extremely slow. It's use should be avoided unless execution speed
	is not an issue.

	</tr>


	<tr>
	<td align=center><b>m</b></td>
	<td>Used to output the application supplied message associated with
	the logging event.</td>
	</tr>

	<tr>
	<td align=center><b>n</b></td>

	<td>Outputs the platform dependent line separator character or
	characters.

	<p>This conversion character offers practically the same
	performance as using non-portable line separator strings such as
	"\n", or "\r\n". Thus, it is the preferred way of specifying a
	line separator.


	</tr>

	<tr>
	<td align=center><b>p</b></td>
	<td>Used to output the level(priority) of the logging event.</td>
	</tr>

	<tr>

	<td align=center><b>r</b></td>

	<td>Used to output the number of milliseconds elapsed since the start
	of the application until the creation of the logging event.</td>
	</tr>


	<tr>
	<td align=center><b>t</b></td>

	<td>Used to output the name of the thread that generated the
	logging event.</td>

	</tr>

	<tr>

	<td align=center><b>x</b></td>

	<td>Used to output the NDC (nested diagnostic context) associated
	with the thread that generated the logging event.
	</td>
	</tr>


	<tr>
	<td align=center><b>X</b></td>

	<td> 

	<p>Used to output the MDC (mapped diagnostic context) associated
	with the thread that generated the logging event. The <b>X</b>
	conversion character <em>must</em> be followed by the key for the
	map placed between braces, as in <b>\%X{clientNumber}</b> where
	<code>clientNumber</code> is the key. The value in the MDC
	corresponding to the key will be output.</p>

	<p>See MDC class for more details.
	</p>

	</td>
	</tr>

	<tr>

	<td align=center><b>\%</b></td>

	<td>The sequence \%\% outputs a single percent sign.
	</td>
	</tr>

	</table>

	<p>By default the relevant information is output as is. However,
	with the aid of format modifiers it is possible to change the
	minimum field width, the maximum field width and justification.

	<p>The optional format modifier is placed between the percent sign
	and the conversion character.

	<p>The first optional format modifier is the <em>left justification
	flag</em> which is just the minus (-) character. Then comes the
	optional <em>minimum field width</em> modifier. This is a decimal
	constant that represents the minimum number of characters to
	output. If the data item requires fewer characters, it is padded on
	either the left or the right until the minimum width is
	reached. The default is to pad on the left (right justify) but you
	can specify right padding with the left justification flag. The
	padding character is space. If the data item is larger than the
	minimum field width, the field is expanded to accommodate the
	data. The value is never truncated.

	<p>This behavior can be changed using the <em>maximum field
	width</em> modifier which is designated by a period followed by a
	decimal constant. If the data item is longer than the maximum
	field, then the extra characters are removed from the
	<em>beginning</em> of the data item and not from the end. For
	example, it the maximum field width is eight and the data item is
	ten characters long, then the first two characters of the data item
	are dropped. This behavior deviates from the printf function in C
	where truncation is done from the end.

	<p>Below are various format modifier examples for the logger
	conversion specifier.

	<p>
	<TABLE BORDER=1 CELLPADDING=8>
	<tr>
	<td align=center><b>Format modifier</b></td>
	<td align=center><b>left justify</b></td>
	<td align=center><b>minimum width</b></td>
	<td align=center><b>maximum width</b></td>
	<td align=center><b>comment</b></td>
	</tr>

	<tr>
	<td align=center>\%20c</td>
	<td align=center>false</td>
	<td align=center>20</td>
	<td align=center>none</td>

	<td>Left pad with spaces if the logger name is less than 20
	characters long.

	<tr> <td align=center>\%-20c</td> <td align=center>true</td> <td
	align=center>20</td> <td align=center>none</td> <td>Right pad with
	spaces if the logger name is less than 20 characters long.

	<tr>
	<td align=center>\%.30c</td>
	<td align=center>NA</td>
	<td align=center>none</td>
	<td align=center>30</td>

	<td>Truncate from the beginning if the logger name is longer than 30
	characters.

	<tr>
	<td align=center>\%20.30c</td>
	<td align=center>false</td>
	<td align=center>20</td>
	<td align=center>30</td>

	<td>Left pad with spaces if the logger name is shorter than 20
	characters. However, if logger name is longer than 30 characters,
	then truncate from the beginning.

	<tr>
	<td align=center>\%-20.30c</td>
	<td align=center>true</td>
	<td align=center>20</td>
	<td align=center>30</td>

	<td>Right pad with spaces if the logger name is shorter than 20
	characters. However, if logger name is longer than 30 characters,
	then truncate from the beginning.

	</table>

	<p>Below are some examples of conversion patterns.

	<dl>

	<p><dt><b>\%r [\%t] \%-5p \%c \%x - \%m\n</b>
	<p><dd>This is essentially the TTCC layout.

	<p><dt><b>\%-6r [\%15.15t] \%-5p \%30.30c \%x - \%m\n</b>

	<p><dd>Similar to the TTCC layout except that the relative time is
	right padded if less than 6 digits, thread name is right padded if
	less than 15 characters and truncated if longer and the logger
	name is left padded if shorter than 30 characters and truncated if
	longer.

	</dl>

	<p>The above text is largely inspired from Peter A. Darnell and
	Philip E. Margolis' highly recommended book "C -- a Software
	Engineering Approach", ISBN 0-387-97389-3.
	*/
	class PatternLayout : public Layout
	{
	public:
		/** Default pattern string for log output. Currently set to the
		string <b>"\%m\%n"</b> which just prints the application supplied
		message. */
		static tstring DEFAULT_CONVERSION_PATTERN;

		/** A conversion pattern equivalent to the TTCCCLayout.
		Current value is <b>\%r [\%t] \%p \%c \%x - \%m\%n</b>. */
		static tstring TTCC_CONVERSION_PATTERN;

	protected:
		static int BUF_SIZE;
		static int MAX_CAPACITY;

	private:
		// output buffer appended to when format() is invoked
		tostringstream sbuf;
		tstring pattern;
		helpers::PatternConverterPtr head;
		tstring timezone;

	public:
		/**
		Does nothing
		*/
		PatternLayout();

		/**
		Constructs a PatternLayout using the supplied conversion pattern.
		*/
		PatternLayout(const tstring& pattern);

		/**
		Set the <b>ConversionPattern</b> option. This is the string which
		controls formatting and consists of a mix of literal content and
		conversion specifiers.
		*/
		void setConversionPattern(const tstring& conversionPattern);

		/**
		Returns the value of the <b>ConversionPattern</b> option.
		*/
		inline tstring getConversionPattern() const
			{ return pattern; }

		/**
		Call createPatternParser
		*/
		virtual void activateOptions();

		virtual void setOption(const tstring& option, const tstring& value);

		/**
		The PatternLayout does not handle the throwable contained within
		{@link spi::LoggingEvent LoggingEvents}. Thus, it returns
		<code>true</code>.
		*/
		virtual bool ignoresThrowable()
			{ return true; }

		/**
		Produces a formatted string as specified by the conversion pattern.
		*/
		virtual void format(tostream& output, const spi::LoggingEvent& event);

	protected:
		/**
		Returns head of PatternParser used to parse the conversion string. 
		Subclasses may override this to return a subclass of PatternParser 
		which recognize custom conversion characters.
		*/
		virtual helpers::PatternConverterPtr createPatternParser(const tstring& pattern);
	};
}; // namespace log4cxx

#endif //_LOG4CXX_PATTERN_LAYOUT_H
