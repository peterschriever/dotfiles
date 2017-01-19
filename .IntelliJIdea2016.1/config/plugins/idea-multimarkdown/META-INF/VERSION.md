### 1.5.0 - Bug Fix & Optimization Release

#### Basic & Enhanced Editions

- Add: patch release and eap update streams 
- Fix: syntax highlighting inline elements in definition text 
- Add: HTML entity syntax highlighting.
- Fix: Comments with todo items would not show up in to do list when syntax highlighting was set
  to annotator. Now comments are parsed by the plain text lexer used to disable lexer syntax
  highlighting. 
- Fix: update highlight.js to version 9.3.0 and include all available languages.
- Add: live templates starting with `.` 

    | Element       | Abbreviation    | Expansion                                               |
    |---------------|-----------------|---------------------------------------------------------|
    | Abbreviation  | `.abbreviation` | `*[]: `                                                 |
    | Code fence    | `.codefence`    | \`\`\` ... \`\`\`                                       |
    | Explicit link | `.link`         | `[]()`                                                  |
    | Footnote      | `.footnote`     | `[^]: `                                                 |
    | Footnote Ref  | `.rfootnote`    | `[^]`                                                   |
    | Image         | `.image`        | `![]()`                                                 |
    | Ref image     | `.rimage`       | `![][]`                                                 |
    | Ref link      | `.rlink`        | `[][]`                                                  |
    | Reference     | `.reference`    | `[]: `                                                  |
    | Table         | `.table`        | <pre><code>`|   |`&#10;`|---|`&#10;`|   |`</code></pre> |
    | Task          | `.task`         | `- [ ] `                                                |
    | Wiki link     | `.wikilink`     | `[[]]`                                                  |

#### Enhanced Edition

* Fix: #195, License activation being reset when no network connection is available.
* Fix: #196, Incorrect parsing of compound reference links
* Fix: #198, Image links that don't end with an extension don't get recognized. Now image links
  without extension are assumed to be correct. No error or warning is generated for these links.
  Query strings are also stripped from the link address before looking for an extension.
* Fix: #199, Multi-line image URLs not parsed correctly when terminating ) is followed by white
  space characters file and without EOL.
* Fix: #201, Image link completion in wiki pages leaves out subdirectories 
* Fix: #211, Completions for some empty link elements show no suggestions.
* Add: highlighting of auto-inserted `*`, `_` or `~` that would be deleted if a space is typed.
* Change: Auto-format table on typing and smart `*` `~` duplication to be off by default. 
* Add: Auto inserted `*`, `_` and `~` that will be deleted by typing a space are now colored in
  the scheme's comment color to highlight that they can be deleted by typing a space
* Fix: block quote prefix on fenced code would not be stripped off. Prefix needs to be
  consistent on all the lines for the prefix to be properly stripped for the injected language
  fragment. 
    
* **List editing features**
    * Add: #210, List item un-indent/indent toolbar buttons, and actions. List item
      un-indent/indent toolbar buttons, assigned to Ctrl-Y/Ctrl-U respectively. 
    * Fix: #209, lines ending in `* ` or `- ` would be erroneously handled as empty list items
      by BACKSPACE handler.
    * Fix: second list items would not enable the indent list action. 
    
* **Table editing features**
    * Fix: #212, Table formatting while typing sometimes causes the cursor to jump erratically
      to end of table.
    * Add: #214, Feature: add insert table toolbar button
    * Add: #215, Feature: table insert/delete row/column toolbar buttons
    * Add: #216, On ENTER insert table row with configuration options
    * Add: #217, On BACKSPACE delete empty table row/column with configuration options
    * Add: Syntax highlighting colors for table header cells separate from table body cells.
    * Fix: as you type table parsing changed to use pegdown instead of hand rolled parser.
      Handles escaped pipes and pipes in code spans correctly.
    * Fix: toggle actions: bold, italic, code, strikethrough; to select text when toggling the
      effect off.
    * Add: logic to disable `auto-format table on typing` when modifying a table causes it to no
      longer have the same number of columns on all rows for editing actions that may be partial
      modifications and if `Add missing columns` is enabled. ie. backspacing or typing back
      ticks, backslash or pipe characters.
    * Fix: reformatting tables without lead/trail pipes would loose the last columns that were
      blank. Now a trailing pipe is added if the column is blank to preserve the correct column
      count.
    * Fix: reformatting tables that were not terminated by a blank line would delete text after
      table up to a blank line.
    * Fix: Mitigate effects of table cell containing unterminated strong, emphasis or strike
      through markers which absorb all text until a blank line. Now this condition is detected
      and wrap on typing and auto-format table are turned off to prevent messing up the format.
    * Fix: Adjust caret to be at the pipe symbol when typing before the first table column.
      Otherwise indentation could be changed causing the table to no longer be valid.
    
* **Auto-format and Wrap on typing features**
    * Add: Toolbar buttons for toggle Auto-format and toggle wrap on typing. 
    * Fix: #202, Plain text paragraphs that have indentation spaces do not get properly wrapped
      as you type.
    * Fix: made wiki link elements non-wrap so that they will not be wrapped across lines.
    * Fix: intermittent wrap on typing failure to wrap paragraphs
    * Fix: #205, Wrap on typing of paragraphs with embedded multi-line URL images will only wrap
      text before the image. Now for the purpose of wrapping these image links are treated as
      paragraph breaks and each segment is wrapped separately.
    * Fix: extra spaces added at end of wrapped text lines. Now only hard break spaces will be
      kept at end of text lines.
    * Add: #206, Wrap on typing continuation line indenting now has the following options:
        * None - continuation lines will start at column 1
        * **Align text edge - default**. Will align continuation lines with the text of the
          first line
        * Indent - continuation lines will start at indent of first line
        * Indent +1 level - continuation lines will start at indent of first line + 4 spaces
        * Indent +2 levels - continuation lines will start at indent of first line + 8 spaces
    * Fix: #207, Markdown hard break spaces are not always be preserved when formatting
      paragraphs
    * Fix: #208, Auto links are not recognized as inline elements during wrap on typing
      reformatting op
    * Fix: #213, Enabling HARD WRAPS in parser options prevents wrap on typing of list items
      that span multiple lines. HARD WRAPS parser extension is now disabled for purposes of
      syntax highlighting and PSI generation. It is only used for HTML rendering.
    * Add: logic to disable `wrap on typing` when modifying a table causes it to no longer be a
      valid markdown table
    * Add: tooltip when `wrap on typing` or `auto-format table on typing` is automatically
      disabled.
    * Add: logic to disable `wrap on typing` when a block is not terminated by a blank line and
      the following block can be potentially merged into the paragraph.
    
* **Typing response optimizations**
    * Fix: #19, Optimize typing response with or without wrap on typing and table reformat
    * minimize updates to unchanged parts of the paragraph or table 
    * handle IDE skipping calls to handlers when fast typing (or rolling forehead on the
      keyboard).
    * HTML generation was not disabled when only main editor was shown. This would cause
    * Changed default syntax highlighter to external annotator based to reduce typing delay. If
      you want to use lexer based syntax highlighting you will need to change it in
      settings/preferences.
    * disabled html generation when preview is not shown
    
    Fastest typing response is achieved when:
    
    * syntax highlighting is turned off
    * wrap on typing is disabled
    * auto-format tables is disabled
    * all previews are turned off

* **Jekyll front matter handling**
    * Fix: #200, Jekyll front matter is not recognized if the terminating marker is at the end
      of file.
    * #222 Inspection to detect Jekyll front matter presence in the file, with option to enable
      or ignore.
    * Code style option to not splice image and explicit links which are start of line to
      previous line during paragraph reformatting.
    * Jekyll front matter folding region and config

### 1.4.10 - Bug Fix & Optimization Release

#### Basic & Enhanced Editions

- Fix: book icon in preview would not open document in browser
- Fix: incorrect HTML rendering of undefined reference link `[some-text][]` as
  `[some-text][some-text]`

#### Enhanced Edition

* Add: list item handling on <kbd>ENTER</kbd> and <kbd>BACKSPACE</kbd>. <kbd>ENTER</kbd> will
  add unordered item or ordered item depending on what is preceding caret location.
  <kbd>ENTER</kbd> and <kbd>BACKSPACE</kbd> will remove empty list items. Configuration to
  enable/disable in Editor > Code Style > MultiMarkdown under `List Items`
* Improve: auto format handling on typing, <kbd>ENTER</kbd> and <kbd>BACKSPACE</kbd>
* Add: table formatting via the format toolbar button
* Add: table formatting option to format as you type in table separator line

### 1.4.9 - Bug Fix & Optimization Release 

#### Basic & Enhanced Editions

- Add: formatting buttons
- Add: markdown specific soft-wrap setting. This only affects the editor when it is first
  opened. Thereafter use keyboard shortcuts to toggle soft wrap mode.
    - default - uses global setting
    - disabled - always opens editor with soft-wraps turned off
    - enabled - always opens editor with soft-wraps turned on
- Fix #190, Incorrect parsing of HTML blocks. This also fixes improper handling of HTML block
  suppression.

#### Enhanced Edition

* Add: handling of Jekyll front matter in markdown documents. Document must start with `---` and
  have another `---` terminating the front matter for it not to be parsed as Markdown.
* Add: option to embed CSS resources into the HTML document instead of URL links

### 1.4.8 - Bug Fix & Optimization Release

#### Basic & Enhanced Editions

- Add: option for syntax highlighting type either lexer based, external annotator or none at all
- Fix: #176, Exception: Panel is guaranteed to be not null now
- Fix: #180, code syntax highlighting has border around code blocks in HTML preview.
- Fix: #183, Incomplete Tasks in Task list not rendering correctly
- Fix: #182, Light scroll bars showing in dark theme. Added CSS to change WebView scroll bar
  colors.
- Fix: #178, Chinese character display problem. Headings would be empty if they contained only
  non-ascii alpha characters.
- Fix: #184, Smooth scroll issues with preview. Reduce frequency of on scroll callbacks to
  reduce delay during scrolling.
- Fix: #185, IntelliJ IDEA performance is heavily affected by this plug-in. Pegdown bug causes
  exponential parse time for markdown with unclosed HTML tags and fenced code blocks that
  contain HTML.

#### Enhanced Edition

* Add: parsing of HTML anchor elements with id for resolving, annotating duplicates and finding
  usages for ref anchors. Only the opening tag is significant: `<a id='ref-anchor'>` or `<a
  id="ref-anchor">`
* Change: anchor ref completion shows header level and text, for ref anchors shows complete
  opening tag
* Fix: optimizations that skip reformatting to be less optimistic improving wrap on typing
  results.
* Add: handling of non-wrap inline elements that cannot handle being wrapped across lines.
  Embedded spaces in these elements are now treated as non-break spaces.
* Add: reformat document action which for now formats the current paragraph.

### 1.4.7 - Bug Fix & Optimization Release

#### Basic & Enhanced Editions

- Fix: #164, PyCharm & RubyMine highlight a single space at the end of the line as Markdown HARD
  BREAK
- Fix: #167, NoSuchMethodError when typing text
- Fix: #169, IndexOutOfBoundsException chars sequence.length:5, start:-1, end:5
- Add: external annotator to reduce typing delay.

#### Enhanced Edition

* Fix: #165, Reference Images and Links split across a line boundary show as unresolved
* Fix: #166, Image Links embedded in text are not recognized as inline elements that can be
  wrapped.
* Fix: #168, Optimize wrap on typing to not reformat text block on every typed character

### 1.4.6 - Bug Fix Release

#### Basic & Enhanced Editions

- Fix: #163, NullPointerException on new files

### 1.4.5 - Bug Fix & Enhancements Release
