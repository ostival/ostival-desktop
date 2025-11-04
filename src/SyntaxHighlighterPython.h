/*
=========================================
Text Editor Syntax Highlighter for Python
-----------------------------------------
Coded by:
Team Ostival (hello@ostival.org)
-----------------------------------------
*/
#ifndef SYNTAXHIGHLIGHTERPYTHON_H
#define SYNTAXHIGHLIGHTERPYTHON_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>
#include <QVector>

class SyntaxHighlighterPython : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit SyntaxHighlighterPython(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> highlightingRules;
    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
};

#endif