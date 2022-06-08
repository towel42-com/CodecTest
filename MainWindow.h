// The MIT License( MIT )
//
// Copyright( c ) 2020-2021 Scott Aron Bloom
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files( the "Software" ), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QDialog>
#include <memory>
class QLineEdit; 
class QFile;
class QTextStream;
namespace Ui
{
    class CMainWindow;
}

class CMainWindow : public QDialog
{
    Q_OBJECT
public:
    CMainWindow( QWidget * parent = nullptr );
    virtual ~CMainWindow() override;

public Q_SLOTS:
    void slotEnglishChangedNoData();
    void slotGermanChangedNoData();
    void slotHindiChangedNoData();
    void slotHebrewChangedNoData();

    void slotEnglishChangedWithData( const QString & text );
    void slotGermanChangedWithData( const QString & text );
    void slotHindiChangedWithData( const QString & text );
    void slotHebrewChangedWithData( const QString & text );

    void slotLoadDefaults();
private:
    void displayData( const QString & label, QLineEdit * le );
    void displayData( const QString & label, const QString & text, bool fromText );

    std::unique_ptr< Ui::CMainWindow > fImpl;
    
    std::shared_ptr< QFile > fFile;
    std::shared_ptr< QTextStream > fTextStream;
};
#endif 
