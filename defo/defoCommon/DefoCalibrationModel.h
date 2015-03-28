#ifndef DEFOCALIBRATIONMODEL_H
#define DEFOCALIBRATIONMODEL_H

#include <QObject>

class DefoCalibrationModel : public QObject
{
    Q_OBJECT
public:
  explicit DefoCalibrationModel(QObject *parent = 0);

  void setCalibX(double v);
  void setCalibY(double v);
  void setCalibZ(double v);

  double getCalibX() const { return calibX_; }
  double getCalibY() const { return calibY_; }
  double getCalibZ() const { return calibZ_; }

  void write(const QString& filename);
  void read(const QString& filename);

public slots:

protected:

  double calibX_;
  double calibY_;
  double calibZ_;

signals:

  void calibrationChanged();
};

#endif // DEFOCALIBRATIONMODEL_H
