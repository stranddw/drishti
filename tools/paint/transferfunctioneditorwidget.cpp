#include "transferfunctioneditorwidget.h"

TransferFunctionEditorWidget::TransferFunctionEditorWidget(QWidget *parent) :  
  QSplitter(Qt::Vertical, parent)
{
  m_parent = parent;

  m_splineEditorWidget = new SplineEditorWidget(this);
  m_gradientEditorWidget = new GradientEditorWidget(this);

  addWidget(m_splineEditorWidget);
  addWidget(m_gradientEditorWidget);

  QList<int> ssz;
  ssz << 150 << 75;
  setSizes(ssz);

  setChildrenCollapsible(false);

  QObject::connect(m_gradientEditorWidget, SIGNAL(gradientChanged(QGradientStops)),
		   m_splineEditorWidget, SLOT(setGradientStops(QGradientStops)));

  QObject::connect(m_splineEditorWidget, SIGNAL(selectEvent(QGradientStops)),
		   m_gradientEditorWidget, SLOT(setColorGradient(QGradientStops)));

  QObject::connect(m_splineEditorWidget, SIGNAL(transferFunctionChanged(QImage)),
		   this, SLOT(transferFunctionChanged(QImage)));
}


TransferFunctionEditorWidget::~TransferFunctionEditorWidget()
{
  delete m_splineEditorWidget;
  delete m_gradientEditorWidget;
}

void
TransferFunctionEditorWidget::setTransferFunction(SplineTransferFunction *stf)
{
  m_splineEditorWidget->setTransferFunction(stf);

  if (stf)
    {
      m_gradientEditorWidget->setColorGradient(stf->gradientStops());
    }
  else
    {
      QGradientStops gradStops;
      gradStops << QGradientStop(0.0, QColor(0,0,0, 0))
		<< QGradientStop(1.0, QColor(0,0,0, 0));
      
      m_gradientEditorWidget->setColorGradient(gradStops);
    }

  update();
}


void
TransferFunctionEditorWidget::setMapping(QPolygonF fmap)
{
  m_splineEditorWidget->setMapping(fmap);
}

void
TransferFunctionEditorWidget::setHistogramImage(QImage histImage1,
						QImage histImage2)
{
  m_splineEditorWidget->setHistogramImage(histImage1, histImage2);
  update();
}

void
TransferFunctionEditorWidget::setHistogram2D(int *hist2D)
{
  m_splineEditorWidget->setHistogram2D(hist2D);
  update();
}

void
TransferFunctionEditorWidget::transferFunctionChanged(QImage lookupTable)
{
  update();
  emit transferFunctionUpdated(lookupTable);
  emit updateComposite();
}
