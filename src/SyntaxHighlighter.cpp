/*
==============================================================================================
Text Editor Syntax Highlighter

Selected Keywords:
always, and, assign, case, casex, casez, deassign, default, else, end, endcase, endgenerate, 
endmodule, endtask, event, for, force, forever, fork, function, generate, genvar, if, include,
initial, inout, input, integer, join, localparam, module, nand, negedge, nor, not, or, output,
parameter, posedge, reg, repeat, signed, task, unsigned, wait, while, wire, xnor, xor.

Selected compiler directive:
define, undef, ifdef, ifndef, else, elsif, endif, include, timescale, default_nettype, pragma.

Selected system and tasks:
$display, $write, $strobe, $monitor, $time, $realtime, $bits, $fopen, $fclose, $fdisplay, $fwrite,
$readmemb, $readmemh, $finish, $stop, $exit, $setup, $hold, $setuphold, $itor, $rtoi, $signed,
$unsigned, $random.
----------------------------------------------------------------------------------------------
Coded by:
Team Ostival (hello@ostival.org)
----------------------------------------------------------------------------------------------
*/
#include <QRegularExpression>
#include <QTextCharFormat>
#include <QColor>
#include <QFont>
#include "SyntaxHighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(QColor("#0077CC"));
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywords = {"module", "endmodule", "input", "output", "wire", "reg","assign", "if", "else", "case", "for", "while", "always"};
    for (const QString &word : keywords)
        highlightingRules.append({QRegularExpression("\\b" + word + "\\b"), keywordFormat});

    keywordFormat.setForeground(QColor("#a0cc00"));
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList custonkeywords = {"begin", "end"};
    for (const QString &word : custonkeywords)
        highlightingRules.append({QRegularExpression("\\b" + word + "\\b"), keywordFormat});

    highlightingRules.append({QRegularExpression("`include\\b"), keywordFormat});
    highlightingRules.append({QRegularExpression("`define\\b"), keywordFormat});

    /*
    Single Line Comment Highlight
    */
    singleLineCommentFormat.setForeground(QColor("#b2b5b2"));
    highlightingRules.append({QRegularExpression("//[^\n]*"), singleLineCommentFormat});

    /*
    Multi-Line Comment Highlight
    */
    multiLineCommentFormat.setForeground(QColor("#b2b5b2"));
    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression   = QRegularExpression("\\*/");
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{

    for (const auto &rule : highlightingRules) {
        QRegularExpressionMatchIterator i = rule.pattern.globalMatch(text);
        while (i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

    while (startIndex >= 0) {
        QRegularExpressionMatch endMatch;
        int endIndex = text.indexOf(commentEndExpression, startIndex);
        int commentLength;

        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex + 2;
        }

        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
