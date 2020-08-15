/************************************************************************
**
**  Copyright (C) 2015-2020 Kevin B. Hendricks, Stratford Ontario Canada
**  Copyright (C) 2011      John Schember <john@nachtimwald.com>
**
**  This file is part of Sigil.
**
**  Sigil is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  Sigil is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Sigil.  If not, see <http://www.gnu.org/licenses/>.
**
*************************************************************************/

#pragma once
#ifndef SPELLCHECK_H
#define SPELLCHECK_H

#include <QHash>
#include <QString>
#include <QStringList>
#include <QMutex>

class Hunspell;
class QStringList;
class QTextCodec;

/**
 * Singleton.
 */
class SpellCheck
{
public:
    struct HDictionary {
        QString    name;
        Hunspell   *handle;
        QTextCodec *codec;
        QString    wordchars;
    };

    static SpellCheck *instance();
    ~SpellCheck();

    QStringList userDictionaries();
    QStringList dictionaries();
    QString currentDictionary() const;

    bool spell(const QString &word);
    QStringList suggest(const QString &word);

    bool spellPS(const QString &word);
    QStringList suggestPS(const QString &word);

    void clearIgnoredWords();
    void ignoreWord(const QString &word);
    void ignoreWordInDictionary(const QString &word);

    QString getWordChars(const QString &lang="");
    void loadDictionary(const QString &name);
    void UnloadDictionary(const QString &name);
    void UnloadAllDictionaries();

    void setDictionary(const QString &name, bool forceReplace = false);
    void reloadDictionary();

    void addToUserDictionary(const QString &word, QString dict_name = "");
    QStringList allUserDictionaryWords();
    QStringList userDictionaryWords(QString dict_name);

    /**
     * The location of the user dictionary directories.
     */
    static QString dictionaryDirectory();
    static QString userDictionaryDirectory();
    static QString currentUserDictionaryFile();
    static QString userDictionaryFile(QString dict_name);

    void loadDictionaryNames();

private:
    SpellCheck();
    QHash<QString, QString> m_dictionaries;
    QHash<QString, QString> m_langcode2dict;
    mutable QMutex mutex;
    QHash<QString, struct HDictionary> m_opendicts;
    QStringList m_ignoredWords;

    static SpellCheck *m_instance;
};

#endif // SPELLCHECK_H
