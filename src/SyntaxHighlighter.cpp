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

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent){
    
    QTextCharFormat keywordFormat;
    QStringList module_words = {"module", "endmodule", "input", "output", "inout"};
    QStringList pair_words = {"begin", "end", "if", "else", "case", "casex", "endcase"};
    QStringList connection_words = {"wire", "reg", "posedge", "negedge"};
    QStringList compiler_words = {"`include", "`define", "`timescale","`undef", "`ifdef", "`else","`endif", "`ifndef"};
    QStringList system_words = {"$display", "$fopen", "$fclose"};
    QStringList behavioural_words = {"initial", "always"};
    QStringList gate_level_words = {"and","or","not","nand","nor","xor","xnor"};

    keywordFormat.setFontWeight(QFont::Bold);

    keywordFormat.setForeground(QColor("#0077CC"));
    for (const QString &word : module_words)
        highlightingRules.append({QRegularExpression("\\b" + word + "\\b"), keywordFormat});

    keywordFormat.setForeground(QColor("#a0cc00"));
    for (const QString &word : pair_words)
        highlightingRules.append({QRegularExpression("\\b" + word + "\\b"), keywordFormat});

    keywordFormat.setForeground(QColor("#f4d042"));
    for (const QString &word : connection_words)
        highlightingRules.append({QRegularExpression("\\b" + word + "\\b"), keywordFormat});

    keywordFormat.setForeground(QColor("#ff9646"));
    for (const QString &word : behavioural_words)
        highlightingRules.append({QRegularExpression("\\b" + word + "\\b"), keywordFormat});
    
    keywordFormat.setForeground(QColor("#ff4646"));
    for (const QString &word : gate_level_words)
        highlightingRules.append({QRegularExpression("\\b" + word + "\\b"), keywordFormat});
    
    keywordFormat.setForeground(QColor("#eb3be8"));
    for (const QString &word : system_words)
        highlightingRules.append({ QRegularExpression(QRegularExpression::escape(word) + "(?!\\w)"), keywordFormat });

    keywordFormat.setForeground(QColor("#36cbd9"));
    for (const QString &word : compiler_words)
        highlightingRules.append({QRegularExpression(QRegularExpression::escape(word) + "(?!\\w)"), keywordFormat});

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
