/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//               Copyright (C) 2011-2017 - The DESY CMS Group                  //
//                           All rights reserved                               //
//                                                                             //
//      The CMStkModLab source code is licensed under the GNU GPL v3.0.        //
//      You have the right to modify and/or redistribute this source code      //
//      under the terms specified in the license, which may be found online    //
//      at http://www.gnu.org/licenses or at License.txt.                      //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////

#ifndef ASSEMBLYTHRESHOLDVIEW_H
#define ASSEMBLYTHRESHOLDVIEW_H

#include <AssemblyUEyeView.h>

#include <QWidget>
#include <QScrollArea>
#include <QKeyEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include <opencv2/opencv.hpp>

class AssemblyThresholdView : public QWidget
{
 Q_OBJECT

 public:

  explicit AssemblyThresholdView(QWidget* parent=nullptr);
  virtual ~AssemblyThresholdView() {}

  int get_threshold() const;

  void    connectImageProducer_1(const QObject* sender, const char* signal);
  void disconnectImageProducer_1(const QObject* sender, const char* signal);

  void    connectImageProducer_2(const QObject* sender, const char* signal);
  void disconnectImageProducer_2(const QObject* sender, const char* signal);

 protected:

  void keyReleaseEvent(QKeyEvent*);

  AssemblyUEyeView* imageView_1_;
  AssemblyUEyeView* imageView_2_;

  QScrollArea* scrollArea_1_;
  QScrollArea* scrollArea_2_;

  QPushButton* imgraw_button_;
  QPushButton* imgbin_button_;

  QPushButton* thresh_button_;
  QLabel*      thresh_label_;
  QLineEdit*   thresh_linee_;

 public slots:

  void read_threshold();

  void save_image_raw();
  void save_image_bin();

  void save_image(const cv::Mat&);

 signals:

  void threshold_value(const int);

  void image_raw_request();
  void image_bin_request();
};

#endif // ASSEMBLYTHRESHOLDVIEW_H
