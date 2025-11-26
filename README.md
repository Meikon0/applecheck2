Разработано в Технологическом университете «AuroraLab»
# AppleCheck

Мобильное приложение под ОС Аврора для оценки качества яблок с поддержкой офлайн-дообучения модели. Проект включает QML-интерфейс, NCNN/TFLite-инференс и MlPack-тренер для инкрементального обучения на устройстве.

## Возможности
- Захват фото с камеры (CameraImageCapture) или выбор из галереи.
- Классификация: «Хорошее яблоко», «Плохое яблоко», «Не яблоко».
- Подсказки по съемке и понятный QML-интерфейс.
- Локальное дообучение на устройстве (MlPack/TFLite).
- Совместимость с эмулятором и устройствами ОС Аврора.

## Архитектура (текстовая диаграмма)
```
[QML UI]
  ├─ HomePage (камера/галерея, предпросмотр, анализ)
  ├─ TrainingPage (сбор и запуск дообучения)
  └─ ResultDialog (вывод ответа)
[AppController QObject]
  ├─ CameraHandler (QCamera + QCameraImageCapture)
  ├─ ImageProcessor (OpenCV препроцессинг)
  ├─ AppleClassifier
  │   ├─ NcnnInference (YOLO11-segm/YOLACT для масок)
  │   └─ TfliteInference (легкий классификатор)
  ├─ MlPackTrainer (локальное обучение)
  └─ AppSettings (QSettings хранилище)
[Models]
  ├─ labels.txt
  └─ initial_weights.bin
```

## Сборка в Aurora SDK
1. Установите Aurora SDK и Conan с доступом к удалённому `aurora-conan`.
2. Установите зависимости:
   ```bash
   conan install . -of build -b missing
   ```
3. Соберите проект через CMake Aurora SDK:
   ```bash
   cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=$AURORA_SDK/toolchain.cmake
   cmake --build build
   ```
4. Запустите на устройстве/эмуляторе:
   ```bash
   ./build/bin/AppleCheck
   ```

## Примеры интеграции NCNN / YOLACT / YOLO11-segm
```cpp
// NcnnInference::infer псевдокод
ncnn::Extractor ex = net.create_extractor();
ex.input("images", ncnn::Mat::from_pixels_resize(rgb.data, ncnn::Mat::PIXEL_RGB, w, h, 640, 640));
ex.extract("output", feat);
// Декодирование масок YOLACT или сегментов YOLO11-segm => список боксов и классов
```

## Результаты классификации
- «Хорошее яблоко» — высокая уверенность детектора и классификатора.
- «Плохое яблоко» — дефекты/пятна/гниль.
- «Не яблоко» — низкая уверенность или другой объект.

## Оптимизация под мобильные устройства
- Используйте NCNN Vulkan (если доступно) и INT8-квантование TFLite.
- Обрезайте вход до 320×320, батч 1, включайте prefetch и zero-copy буферы.
- В MlPack снижайте глубину сети и применяйте раннюю остановку.
- Кэшируйте результаты препроцессинга и держите модели в памяти.
- Снижайте частоту кадров при превью и выключайте автофокус после захвата.

## Структура репозитория
- `qml/` — QML интерфейс и компоненты.
- `src/core/` — C++ бизнес-логика и ИИ-модули.
- `src/models/` — веса и подписи классов.
- `res/` — иконки и ресурсы.

## Лицензия
Проект распространяется по лицензии BSD-3-Clause (см. LICENSE).
