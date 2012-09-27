#ifndef DEFOIMAGEWIDGET_H
#define DEFOIMAGEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QDateTime>
#include <QSize>

#include "DefoCameraModel.h"
#include "DefoMeasurementListModel.h"
#include "DefoMeasurementSelectionModel.h"
#include "DefoPointRecognitionModel.h"

class DefoImageBaseWidget : public QWidget
{
    Q_OBJECT
public:
  DefoImageBaseWidget(
      QWidget *parent = 0
  );

protected:
  virtual void paintEvent(QPaintEvent *event) = 0;

  /// Subroutine for paintEvent that prepares the image to be drawn.
  virtual QImage prepareImage(const QImage& image) const = 0;

  static const QSize MINIMUM_SIZE;
  QSize getImageDrawingSize(const QImage& image) const;

};

class DefoImageWidget : public DefoImageBaseWidget
{
    Q_OBJECT
public:
  explicit DefoImageWidget(
      DefoMeasurementSelectionModel* model
    , QWidget *parent = 0
  );

protected:
  DefoMeasurementSelectionModel* selectionModel_;
  void paintEvent(QPaintEvent *event);

  /// Subroutine for paintEvent that prepares the image to be drawn.
  virtual QImage prepareImage(const QImage& image) const = 0;

public slots:
  virtual void selectionChanged(const DefoMeasurement* measurement);

};

class DefoLiveViewImageWidget : public DefoImageBaseWidget
{
    Q_OBJECT
public:
  explicit DefoLiveViewImageWidget(
      DefoCameraModel* model
    , QWidget *parent = 0
  );

protected:
  DefoCameraModel* cameraModel_;
  void paintEvent(QPaintEvent *event);

  /// Subroutine for paintEvent that prepares the image to be drawn.
  QImage prepareImage(const QImage& image) const;

public slots:
  virtual void newLiveViewImage(QString location);

};

/// Displays the raw camera image.
class DefoRawImageWidget : public DefoImageWidget {

    Q_OBJECT
public:
  explicit DefoRawImageWidget(
      DefoMeasurementSelectionModel* model
    , QWidget *parent = 0
  );

  QImage prepareImage(const QImage& image) const;

};

/// Displays a visualisation of the current point recognition thresholds.
class DefoImageThresholdsWidget : public DefoImageWidget {

  Q_OBJECT
public:
  explicit DefoImageThresholdsWidget(
      DefoMeasurementSelectionModel* selectionModel
    , DefoPointRecognitionModel* recognitionModel
    , QWidget *parent = 0
  );

  QImage prepareImage(const QImage& image) const;

public slots:
  void thresholdChanged(
      DefoPointRecognitionModel::Threshold threshold
    , int value
  );
  void selectionChanged(const DefoMeasurement* measurement);

protected:
  DefoPointRecognitionModel* recognitionModel_;
  QImage imageCache_;
  void updateCache();

};

/*
  POINT RECOGNITION DISPLAY
  */

class DefoImagePointsWidget : public DefoRawImageWidget {
  \
  Q_OBJECT
public:
  explicit DefoImagePointsWidget(
      DefoMeasurementListModel *listModel
    , DefoMeasurementSelectionModel *selectionModel
    , QWidget *parent
  );

protected:
  DefoMeasurementListModel* listModel_;
  void paintEvent(QPaintEvent *event);

protected slots:
  void pointsUpdated(const DefoMeasurement* measurement);

};

#endif // DEFOIMAGEWIDGET_H