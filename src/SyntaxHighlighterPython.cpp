/*
==============================================================================================
Text Editor Syntax Highlighter for Python

['False', 'None', 'True', 'and', 'as', 'assert', 'async', 'await', 'break', 'class', 'continue', 
'def', 'del', 'elif', 'else', 'except', 'finally', 'for', 'from', 'global', 'if', 'import', 'in', 
'is', 'lambda', 'nonlocal', 'not', 'or', 'pass', 'raise', 'return', 'try', 'while', 'with', 'yield']
----------------------------------------------------------------------------------------------
Coded by:
Team Ostival (hello@ostival.org)
----------------------------------------------------------------------------------------------
*/
#include <QRegularExpression>
#include <QTextCharFormat>
#include <QColor>
#include <QFont>
#include "SyntaxHighlighterPython.h"

SyntaxHighlighterPython::SyntaxHighlighterPython(QTextDocument *parent) : QSyntaxHighlighter(parent){
    
    QTextCharFormat keywordFormat;
    QStringList import_words = {"import", "assert", "async", "await", "from", "global"};
    QStringList function_words = {"def", "return", "class", "try"};
    QStringList pair_words = {"if", "else", "elif"};
    QStringList loop_words = {"break", "continue", "for", "in", "while"};
    QStringList logic_words = {"and", "not", "or", "True", "False", "None"};
    QStringList other_words = {"as", "del", "except", "finally", "is", "lambda", "nonlocal", "pass", "raise", "with", "yield"};


    keywordFormat.setFontWeight(QFont::Bold);

    keywordFormat.setForeground(QColor("#0077CC"));
    for (const QString &word : import_words)
        highlightingRules.append({QRegularExpression("\\b" + word + "\\b"), keywordFormat});

    keywordFormat.setForeground(QColor("#a0cc00"));
    for (const QString &word : function_words)
        highlightingRules.append({QRegularExpression("\\b" + word + "\\b"), keywordFormat});

    keywordFormat.setForeground(QColor("#f4d042"));
    for (const QString &word : pair_words)
        highlightingRules.append({QRegularExpression("\\b" + word + "\\b"), keywordFormat});
    
    keywordFormat.setForeground(QColor("#42e5f4"));
    for (const QString &word : loop_words)
        highlightingRules.append({QRegularExpression("\\b" + word + "\\b"), keywordFormat});
    
    keywordFormat.setForeground(QColor("#f442bf"));
    for (const QString &word : logic_words)
        highlightingRules.append({QRegularExpression("\\b" + word + "\\b"), keywordFormat});
    
    keywordFormat.setForeground(QColor("#f44242"));
    for (const QString &word : other_words)
        highlightingRules.append({QRegularExpression("\\b" + word + "\\b"), keywordFormat});
    

    /*
    Single Line Comment Highlight
    */
    singleLineCommentFormat.setForeground(QColor("#b2b5b2"));
    highlightingRules.append({QRegularExpression("#[^\n]*"), singleLineCommentFormat});

    /*
    Multi-Line Comment Highlight
    */
    multiLineCommentFormat.setForeground(QColor("#b2b5b2"));
    commentStartExpression = QRegularExpression("\"\"\""); 
    commentEndExpression   = QRegularExpression("\"\"\"");
}

void SyntaxHighlighterPython::highlightBlock(const QString &text)
{
    for (const auto &rule : highlightingRules) {
        QRegularExpressionMatchIterator i = rule.pattern.globalMatch(text);
        while (i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    
    // --- 2. Multi-Line Docstring Highlighting ---

    // Block state 1 means we are currently inside a triple-quote block
    setCurrentBlockState(0); 

    int startIndex = 0;
    int searchOffset = 0;
    
    // Start by checking the state from the previous block
    if (previousBlockState() == 1) {
        // We are already inside a block, so we search for the closing delimiter from the start of the line.
        startIndex = 0;
    } else {
        // Not inside a block, so we search for the opening delimiter.
        startIndex = text.indexOf(commentStartExpression); // Search for """
    }
    
    // Loop through all starting/closing delimiters found on this line
    while (startIndex >= 0) {
        
        // --- Determine End Index ---
        if (previousBlockState() == 1) {
            // Case 1: Currently inside a block (searching for the END)
            int endIndex = text.indexOf(commentEndExpression, startIndex); 
            
            if (endIndex == -1) {
                // End not found on this line. The highlight continues to the end of the block.
                int length = text.length() - startIndex;
                setFormat(startIndex, length, multiLineCommentFormat);
                setCurrentBlockState(1); // Keep state as "inside block"
                startIndex = -1; // End the loop for this line
            } else {
                // End found on this line. Block is closed.
                int length = endIndex - startIndex + 3; // +3 for the length of """
                setFormat(startIndex, length, multiLineCommentFormat);
                setCurrentBlockState(0); // State is now "outside block"
                
                // Continue searching for the next *opening* delimiter AFTER the closing one
                searchOffset = startIndex + length;
                startIndex = text.indexOf(commentStartExpression, searchOffset);
            }
        
        } else {
            // Case 2: Currently outside a block (searching for the START)
            
            int endIndex = text.indexOf(commentEndExpression, startIndex + 3); 
            
            if (endIndex == -1) {
                // End not found on this line. Block starts here and continues.
                int length = text.length() - startIndex;
                setFormat(startIndex, length, multiLineCommentFormat);
                setCurrentBlockState(1); // Set state as "inside block"
                startIndex = -1; // End the loop for this line

            } else {
                // Start and End found on the same line (a single-line docstring).
                int length = endIndex - startIndex + 3;
                setFormat(startIndex, length, multiLineCommentFormat);
                setCurrentBlockState(0); // State remains "outside block"
                
                // Continue searching for the next *opening* delimiter AFTER this block
                searchOffset = startIndex + length;
                startIndex = text.indexOf(commentStartExpression, searchOffset);
            }
        }
    }
}