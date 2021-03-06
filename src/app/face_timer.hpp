#ifndef FACE_TIMER_HPP
#define FACE_TIMER_HPP

#include <QObject>

#include <chrono>

#include "detection_data.hpp"
#include "pingpang_buffer.hpp"
#include "quface_common.hpp"

namespace suanzi {
class FaceTimer : QObject {
  Q_OBJECT
 public:
  static FaceTimer* get_instance();

 private slots:
  void rx_frame(PingPangBuffer<DetectionData> *buffer);

 signals:
  // face disappear
  void tx_face_disappear(int disappear_duration);

  // face appear
  void tx_face_appear(int disappear_duration);

 private:
  FaceTimer(QThread *thread = nullptr, QObject *parent = nullptr);
  ~FaceTimer();

  int disappear_counter_;
  int disappear_duration_;
  std::chrono::steady_clock::time_point disappear_begin_;
};

}  // namespace suanzi

#endif
