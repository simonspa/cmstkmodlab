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

#ifndef AssemblyObjectAligner_h
#define AssemblyObjectAligner_h

#include <LStepExpressMotionManager.h>
#include <AssemblyObjectFinderPatRec.h>

#include <QObject>

class AssemblyObjectAligner : public QObject
{
 Q_OBJECT

 public:
  explicit AssemblyObjectAligner(const LStepExpressMotionManager* const, QObject* parent=nullptr);
  virtual ~AssemblyObjectAligner() {}

  void reset();

  class Configuration {

   public:
    explicit Configuration() { this->reset(); }
    virtual ~Configuration() {}

    void reset();

    bool is_valid() const;

    double object_deltaX;
    double object_deltaY;

    bool only_measure_angle;

    double target_angle;

    AssemblyObjectFinderPatRec::Configuration PatRecOne_configuration;
    AssemblyObjectFinderPatRec::Configuration PatRecTwo_configuration;
  };

  const Configuration& configuration() const { return configuration_; }

  protected:

    const LStepExpressMotionManager* const motion_manager_;

    Configuration configuration_;

    bool motion_manager_enabled_;

    void enable_motion_manager(const bool);

    void    connect_motion_manager() { this->enable_motion_manager(true) ; }
    void disconnect_motion_manager() { this->enable_motion_manager(false); }

    // parameters
    double angle_max_dontIter_;
    double angle_max_complete_;
    double angle_PatRec_offset_;

    // transient data (values to be updated during alignment)
    int alignment_step_;

    double posi_x1_, posi_y1_;
    double posi_x2_, posi_y2_;

    double obj_angle_deg_;

  public slots:

    void update_configuration(const Configuration&);

    void execute();

    void run_alignment(int, double, double, double);

    void launch_next_alignment_step();

    void moveRelative(const double, const double, const double, const double);

    void complete_motion();

  signals:

    void configuration_updated();

    void nextAlignmentStep(int, double, double, double);

    void move_relative(const double, const double, const double, const double);

    void motion_completed();

    void acquireImage();

    void measured_angle(const double);

    void execution_completed();
};

#endif // AssemblyObjectAligner_h
