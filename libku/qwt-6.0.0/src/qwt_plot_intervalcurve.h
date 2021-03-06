/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#ifndef QWT_PLOT_INTERVAL_CURVE_H
#define QWT_PLOT_INTERVAL_CURVE_H

#include "qwt_global.h"
#include "qwt_plot_seriesitem.h"
#include "qwt_series_data.h"

class QwtIntervalSymbol;

/*!
  \brief QwtPlotIntervalCurve represents a series of samples, where each value
         is associated with an interval ( \f$[y1,y2] = f(x)\f$ ).

  The representation depends on the style() and an optional symbol()
  that is displayed for each interval. QwtPlotIntervalCurve might be used
  to disply error bars or the area between 2 curves.
*/

class QWT_EXPORT QwtPlotIntervalCurve: public QwtPlotSeriesItem<QwtIntervalSample>
{
public:
    /*!
        \brief Curve styles.
        The default setting is QwtPlotIntervalCurve::Tube.

        \sa setStyle(), style()
    */

    enum CurveStyle
    {
        /*!
           Don't draw a curve. Note: This doesn't affect the symbols.
         */
        NoCurve,

        /*!
           Build 2 curves from the upper and lower limits of the intervals
           and draw them with the pen(). The area between the curves is
           filled with the brush().
         */
        Tube,

        /*!
           Styles >= QwtPlotIntervalCurve::UserCurve are reserved for derived
           classes that overload drawSeries() with
           additional application specific curve types.
         */
        UserCurve = 100
    };

    /*!
        Attributes to modify the drawing algorithm.
        \sa setPaintAttribute(), testPaintAttribute()
    */
    enum PaintAttribute
    {
        /*!
          Clip polygons before painting them. In situations, where points
          are far outside the visible area (f.e when zooming deep) this
          might be a substantial improvement for the painting performance.
         */
        ClipPolygons = 0x01,

        //! Check if a symbol is on the plot canvas before painting it.
        ClipSymbol   = 0x02
    };

    //! Paint attributes
    typedef QFlags<PaintAttribute> PaintAttributes;

    explicit QwtPlotIntervalCurve( const QString &title = QString::null );
    explicit QwtPlotIntervalCurve( const QwtText &title );

    virtual ~QwtPlotIntervalCurve();

    virtual int rtti() const;

    void setPaintAttribute( PaintAttribute, bool on = true );
    bool testPaintAttribute( PaintAttribute ) const;

    void setSamples( const QVector<QwtIntervalSample> & );

    void setPen( const QPen & );
    const QPen &pen() const;

    void setBrush( const QBrush & );
    const QBrush &brush() const;

    void setStyle( CurveStyle style );
    CurveStyle style() const;

    void setSymbol( const QwtIntervalSymbol * );
    const QwtIntervalSymbol *symbol() const;

    virtual void drawSeries( QPainter *p,
        const QwtScaleMap &xMap, const QwtScaleMap &yMap,
        const QRectF &canvasRect, int from, int to ) const;

    virtual QRectF boundingRect() const;
    virtual void drawLegendIdentifier( QPainter *, const QRectF & ) const;

protected:

    void init();

    virtual void drawTube( QPainter *,
        const QwtScaleMap &xMap, const QwtScaleMap &yMap,
        const QRectF &canvasRect, int from, int to ) const;

    virtual void drawSymbols( QPainter *, const QwtIntervalSymbol &,
        const QwtScaleMap &xMap, const QwtScaleMap &yMap,
        const QRectF &canvasRect, int from, int to ) const;

private:
    class PrivateData;
    PrivateData *d_data;
};

Q_DECLARE_OPERATORS_FOR_FLAGS( QwtPlotIntervalCurve::PaintAttributes );

#endif
