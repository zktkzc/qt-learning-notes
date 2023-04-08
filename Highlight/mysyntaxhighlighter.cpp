
#include "mysyntaxhighlighter.h"

#include <QRegExp>
#include <QString>

MySyntaxHighlighter::MySyntaxHighlighter(QObject *parent) : QSyntaxHighlighter(parent)
{

}

MySyntaxHighlighter::~MySyntaxHighlighter()
{

}

void MySyntaxHighlighter::highlightBlock(const QString &text)
{
    QTextCharFormat format;
    format.setFont(QFont("微软雅黑"));
    format.setFontWeight(QFont::Bold);
    format.setForeground(Qt::green);

    // 匹配char
    QString pattern = "\\bchar\\b";
    // 创建正则表达式
    QRegExp express(pattern);
    int index = text.indexOf(express);
    while (index > 0) {
        int matchLen = express.matchedLength();
        setFormat(index, matchLen, format);
        index = text.indexOf(express, index+matchLen);
    }
}
