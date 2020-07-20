#ifndef DETECT_TASK_H
#define DETECT_TASK_H

#include <QObject>
#include <QRect>

#include "config.hpp"
#include "detection_float.h"
#include "image_package.hpp"
#include "pingpang_buffer.hpp"
#include "quface_common.hpp"
#include "recognize_data.hpp"

namespace suanzi {

class DetectTask : QObject {
  Q_OBJECT
 public:
  DetectTask(FaceDetectorPtr detector, QThread *thread = nullptr,
             QObject *parent = nullptr);
  ~DetectTask();

 private:
  void copy_buffer(ImagePackage *pang, DetectionRatio &bgr_detection,
                   DetectionRatio &nir_detection);

 private slots:
  void rx_frame(PingPangBuffer<ImagePackage> *buffer);
  void rx_finish();

 signals:
  void tx_finish();

  // for display
  void tx_bgr_display(DetectionRatio detection);
  void tx_nir_display(DetectionRatio detection);

  // for recognition
  void tx_frame(PingPangBuffer<RecognizeData> *buffer);
  void tx_no_frame();

 private:
  DetectionRatio select_face(std::vector<suanzi::FaceDetection> &detections,
                             int width, int height);

  bool b_tx_ok_;
  bool b_data_ready_;

  FaceDetectorPtr face_detector_;
  RecognizeData *recognize_data1_;
  RecognizeData *recognize_data2_;
  PingPangBuffer<RecognizeData> *pingpang_buffer_;
};

}  // namespace suanzi

#endif
