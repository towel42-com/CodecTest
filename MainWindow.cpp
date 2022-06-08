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

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QTimer>
#include <QDebug>
#include <QFile>
#include <QTextStream>

CMainWindow::CMainWindow( QWidget * parent )
    : QDialog( parent ),
    fImpl( new Ui::CMainWindow )
{
    fImpl->setupUi( this );

    connect( fImpl->lineEditEnglish, &QLineEdit::textChanged, this, &CMainWindow::slotEnglishChangedNoData );
    connect( fImpl->lineEditEnglish, &QLineEdit::textChanged, this, &CMainWindow::slotEnglishChangedWithData );

    connect( fImpl->lineEditGerman, &QLineEdit::textChanged, this, &CMainWindow::slotGermanChangedNoData );
    connect( fImpl->lineEditGerman, &QLineEdit::textChanged, this, &CMainWindow::slotGermanChangedWithData );

    connect( fImpl->lineEditHindi, &QLineEdit::textChanged, this, &CMainWindow::slotHindiChangedNoData );
    connect( fImpl->lineEditHindi, &QLineEdit::textChanged, this, &CMainWindow::slotHindiChangedWithData );

    connect( fImpl->lineEditHebrew, &QLineEdit::textChanged, this, &CMainWindow::slotHebrewChangedNoData );
    connect( fImpl->lineEditHebrew, &QLineEdit::textChanged, this, &CMainWindow::slotHebrewChangedWithData );

    fFile = std::make_shared< QFile >( "textout.txt" );
    fFile->open( QFile::WriteOnly | QFile::Append );
    fTextStream = std::make_shared< QTextStream >( fFile.get() );
    fTextStream->setCodec( "UTF-8" );
    *( fTextStream ) << "===========================================================" << "\n";
    fTextStream->flush();

    QTimer::singleShot( 0, this, &CMainWindow::slotLoadDefaults );
}

CMainWindow::~CMainWindow()
{
}

void CMainWindow::slotLoadDefaults()
{
    fImpl->lineEditEnglish->setText( QString::fromUtf8( u8"This is a test of the national broadcasting system in multiple houses" ) );
    fImpl->lineEditGerman->setText( QString::fromUtf8( u8"Dies ist ein Test des nationalen Rundfunksystems in mehreren Häusern" ) );
    fImpl->lineEditHindi->setText( QString::fromUtf8( u8"यह कई घरों में राष्ट्रीय प्रसारण प्रणाली की परीक्षा है" ) );
    fImpl->lineEditHebrew->setText( QString::fromUtf8( u8"זהו מבחן של מערכת השידור הארצית במספר בתים" ) );
}

void CMainWindow::slotEnglishChangedNoData()
{
    displayData( "English", fImpl->lineEditEnglish );
}

void CMainWindow::slotGermanChangedNoData() 
{
    displayData( "German", fImpl->lineEditGerman );
}

void CMainWindow::slotHindiChangedNoData() 
{
    displayData( "Hindi", fImpl->lineEditHindi );
}

void CMainWindow::slotHebrewChangedNoData() 
{
    displayData( "Hebrew", fImpl->lineEditHebrew );
}

void CMainWindow::slotEnglishChangedWithData( const QString & value )
{
    displayData( "English", value, true );
}

void CMainWindow::slotGermanChangedWithData( const QString & value ) 
{
    displayData( "German", value, true );
}

void CMainWindow::slotHindiChangedWithData( const QString & value ) 
{
    displayData( "Hindi", value, true );
}

void CMainWindow::slotHebrewChangedWithData( const QString & value )
{
    displayData( "Hebrew", value, true );
}

void CMainWindow::displayData( const QString & label, QLineEdit * le )
{
    displayData( label, le->text(), false );
}

void CMainWindow::displayData( const QString & label, const QString & value, bool fromText )
{
    qDebug().noquote() << "From text via signal: " << ( fromText ? "yes" : "no" ) << " Label: " << label << " Value: " << value;
    *( fTextStream ) << "From text via signal: " << ( fromText ? "yes" : "no" ) << " Label: " << label << " Value: " << value << "\n";
    *( fTextStream ) << "===========================================================" << "\n";
    fTextStream->flush();
}
