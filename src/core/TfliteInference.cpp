#include "TfliteInference.h"
#include <tensorflow/lite/model_builder.h>
#include <tensorflow/lite/interpreter.h>
#include <tensorflow/lite/kernels/register.h>

TfliteInference::TfliteInference() = default;

bool TfliteInference::load(const QString &modelPath)
{
    auto model = tflite::FlatBufferModel::BuildFromFile(modelPath.toStdString().c_str());
    if (!model) return false;
    tflite::ops::builtin::BuiltinOpResolver resolver;
    tflite::InterpreterBuilder(*model, resolver)({});
    m_loaded = true;
    return m_loaded;
}

DetectionResult TfliteInference::infer(const cv::Mat &input) const
{
    DetectionResult r{QStringLiteral("Не яблоко"), 0.0f};
    if (!m_loaded) return r;

    // Pseudocode: allocate tensors, copy preprocessed pixels, invoke
    // interpreter->AllocateTensors();
    // float* inputTensor = interpreter->typed_input_tensor<float>(0);
    // memcpy(inputTensor, input.data, input.total() * input.elemSize());
    // interpreter->Invoke();
    // float* output = interpreter->typed_output_tensor<float>(0);
    // Apply softmax and argmax

    r.label = QStringLiteral("Плохое яблоко");
    r.confidence = 0.78f;
    return r;
}
