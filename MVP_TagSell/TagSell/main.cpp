#include <QCoreApplication>
#include <QPdfWriter>
#include <QPageLayout>
#include <QPainter>
#include <QGuiApplication>
#include <QFontDatabase>
#include <QtDebug>

void scalePainterFontSizeToFit(QPainter &painter, QFont &r_font, float _heightToFitIn)
{
    float oldFontSize, newFontSize, oldHeight;

    // Init
    oldFontSize = r_font.pointSizeF();

    // Loop
    for (int i=0 ; i<3 ; i++)
    {
        oldHeight = painter.fontMetrics().boundingRect('D').height();
        newFontSize = (_heightToFitIn / oldHeight) * oldFontSize;
        r_font.setPointSizeF(newFontSize);
        painter.setFont(r_font);
        oldFontSize = newFontSize;
        //qDebug() << "OldFontSize=" << oldFontSize << "HtoFitIn=" << _heightToFitIn << "  fontHeight=" << oldHeight << "  newFontSize=" << newFontSize;
    }

    // End
    r_font.setPointSizeF(newFontSize);
    painter.setFont(r_font);
}

void drawProdcut(const QString &productName, QPainter &painter, QPen &pen, QFont &font)
{
    //Draw margins
    QRectF rectangleProduct(0, 2000, 9910, 1000);
    pen.setColor(Qt::red);
    pen.setWidth(5);
    painter.setPen(pen);
    //painter.drawRect(rectangleProduct);

    scalePainterFontSizeToFit(painter, font, 900);

    // Write product
    painter.setPen(Qt::black);
    QFontMetrics fm(painter.font());
    fm.elidedText(productName, Qt::ElideLeft, 1000);
    qreal pixelsWide = fm.horizontalAdvance(productName);

    if(pixelsWide > 9910)
    {
        throw("O espaço reservado para o campo de produto não comporta tantos caracteres!");
    }
    else
        painter.drawText(rectangleProduct, Qt::AlignCenter, productName);
}

void drawCoinSymbol(const QString &coinSymbol, QPainter &painter, QPen &pen, QFont &font)
{
    //Draw margins
    QRectF rectangleFractionedValue(50, 6000, 1200, 900);
    pen.setColor(Qt::darkMagenta);
    pen.setWidth(5);
    painter.setPen(pen);
    //painter.drawRect(rectangleFractionedValue);

    scalePainterFontSizeToFit(painter, font, 650);

    //Write coin symbol
    painter.setPen(Qt::black);
    QFontMetrics fm(painter.font());
    fm.elidedText(coinSymbol, Qt::ElideLeft, 1000);
    qreal pixelsWide = fm.horizontalAdvance(coinSymbol);

    if(pixelsWide > 1200)
    {
        throw("O espaço reservado para o campo de moeda não comporta tantos caracteres!");
    }
    else
        painter.drawText(rectangleFractionedValue, Qt::AlignCenter, coinSymbol);
}

void drawIntegerValue(const QString &integerValue, QPainter &painter, QPen &pen, QFont &font)
{
    //Draw margins
    QRectF rectangleValue(1250, 3300, 4380, 3500);
    pen.setColor(Qt::darkGreen);
    pen.setWidth(5);
    painter.setPen(pen);
    //painter.drawRect(rectangleValue);

    scalePainterFontSizeToFit(painter, font, 2950);

    //Write integer value
    painter.setPen(Qt::red);
    QFontMetrics fm(painter.font());
    fm.elidedText(integerValue, Qt::ElideLeft, 1000);
    qreal pixelsWide = fm.horizontalAdvance(integerValue);

    if(pixelsWide > 1200)
    {
        throw("O espaço reservado para o campo do valor inteiro não comporta tantos caracteres!");
    }
    else
        painter.drawText(rectangleValue, Qt::AlignCenter, integerValue);
}

void drawCommaAndFractionedValue(const QString &fractionedValue, QPainter &painter, QPen &pen, QFont &font)
{
    //Draw Margins
    QRectF rectangleValue(5750, 3400, 3580, 2550);
    pen.setColor(Qt::darkCyan);
    pen.setWidth(5);
    painter.setPen(pen);
    //painter.drawRect(rectangleValue);

    scalePainterFontSizeToFit(painter, font, 1950);

    //Write fractioned value
    QString commaAndFractionedValue = "," + fractionedValue;
    painter.setPen(Qt::red);
    QFontMetrics fm(painter.font());
    fm.elidedText(fractionedValue, Qt::ElideLeft, 1000);
    qreal pixelsWide = fm.horizontalAdvance(fractionedValue);

    if(pixelsWide > 1200)
    {
        throw("O espaço reservado para o campo de valor fracionado não comporta tantos caracteres!");
    }
    else
        painter.drawText(rectangleValue, Qt::AlignCenter, commaAndFractionedValue);
}

void drawMeasureUnity(const QString &measureUnity, QPainter &painter, QPen &pen, QFont &font)
{
    //Draw Margins
    QRectF rectangleValue(6550, 7300, 1350, 900);
    pen.setColor(Qt::darkYellow);
    pen.setWidth(5);
    painter.setPen(pen);
    //painter.drawRect(rectangleValue);

    scalePainterFontSizeToFit(painter, font, 550);

    //Write Measure Unity
    painter.drawEllipse(QPointF(7200, 7700), 800, 800);
    painter.setPen(Qt::black);
    QFontMetrics fm(painter.font());
    fm.elidedText(measureUnity, Qt::ElideLeft, 1000);
    qreal pixelsWide = fm.horizontalAdvance(measureUnity);

    if(pixelsWide > 1200)
    {
        throw("O espaço reservado para o campo de unidade de medidas não comporta tantos caracteres!");
    }
    else
        painter.drawText(rectangleValue, Qt::AlignCenter, measureUnity);
}

void generatePDF(const QString &filename)
{
    QPdfWriter pdfWriter(filename);
    pdfWriter.setPageMargins(QMargins(0, 0, 0, 0));
    QPainter painter(&pdfWriter);
    QFontDatabase::addApplicationFont("D:\\dev\\MVP_TagSell\\TagSell\\sketch_block\\Sketch_Block.ttf");
    QPen pen;
    QFont font("Sketch Block");

    drawProdcut("ACEM", painter, pen, font);
    drawCoinSymbol("R$", painter, pen, font);
    drawIntegerValue("1167", painter, pen, font);
    drawCommaAndFractionedValue("90", painter, pen, font);
    drawMeasureUnity("Kg", painter, pen, font);

    painter.end();
}


int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    try
    {
        generatePDF("Teste.pdf");
    }  catch (const char * error) {
        qFatal("Um erro ocorreu: %s", error);
    }


    return a.exec();
}
