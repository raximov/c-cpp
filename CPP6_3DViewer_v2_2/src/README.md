# 3DViewer v2.2

C++20 dasturlash tilida yozilgan 3D model ko'rish va ray tracing dasturi.

## Arxitektura

```
src/
├── main.cc                     # Kirish nuqtasi
├── Makefile                    # GNU build tizimi
├── CMakeLists.txt              # CMake build tizimi
├── 3dviewer.pro                # Qt qmake
│
├── model/                      # MVC: Model
│   ├── model_data.h            # Asosiy ma'lumot tuzilmalari (Vec3, Face, ...)
│   ├── vec3.cc                 # Vec3 matematik metodlari
│   ├── obj_parser.h/cc         # OBJ fayl tahlilchisi
│   ├── affine_transform.h/cc   # 4x4 matritsa, TRS transformatsiyalar
│   ├── geometric_objects.h/cc  # Analitik va poligonal figuralar
│   ├── light.h/cc              # Yorug'lik menedjeri
│   ├── camera.h/cc             # Kamera va nur generatsiyasi
│   ├── kd_tree.h/cc            # KD-daraxt (nur-uchburchak tezlashtirish)
│   ├── ray_tracer.h/cc         # Ko'p oqimli ray tracer
│   └── scene.h/cc              # Sahnani boshqarish fasadi
│
├── controller/                 # MVC: Controller
│   └── controller.h/cc         # Yupqa kontroller; Strategy pattern
│
├── view/                       # MVC: View (Qt)
│   ├── main_window.h/cc        # Asosiy oyna; barcha GUI elementlari
│   ├── gl_widget.h/cc          # OpenGL ko'rinish maydoni
│   └── render_preview.h/cc     # Ray trace natijasini ko'rsatish
│
├── utils/
│   ├── stb_image_write.h       # Rasm saqlash (BMP/PNG/JPEG)
│   └── settings_manager.h/cc   # Sozlamalarni saqlash/yuklash
│
└── tests/
    ├── test_parser.cc          # OBJ parser testlari
    ├── test_affine.cc          # Affin transformatsiya testlari
    ├── test_scene.cc           # Sahna va yorug'lik testlari
    └── test_raytracer.cc       # Ray tracer, KD-tree, kamera testlari
```

## Design Patterns (Loyiha talabi: kamida 3)

| Pattern     | Qayerda ishlatilgan                                      |
|-------------|----------------------------------------------------------|
| **MVC**     | `model/`, `controller/`, `view/` papkalar               |
| **Facade**  | `Scene` klassi — barcha model operatsiyalari uchun      |
| **Strategy**| `IRenderStrategy` / `RayTraceStrategy` — render usuli   |
| **Observer**| `SceneObserver` — sahna o'zgarganda GL widget yangilanadi|
| **Singleton**| `SettingsManager` — global sozlamalar do'koni           |
| **Command** | `Command` bazaviy klassi (kengaytirish uchun tayyor)     |

## Qurilish (Build)

### Talablar
- GCC 11+ yoki Clang 14+ (C++20 qo'llab-quvvatlashi bilan)
- Qt5 (Widgets, OpenGL)
- libGL, libGLU
- Google Test (faqat testlar uchun)

### Ubuntu/Debian o'rnatish
```bash
sudo apt install build-essential qt5-default libgl-dev libglu-dev libgtest-dev
```

### Makefile bilan qurilish
```bash
cd src
make all          # Dasturni qurish
make install      # ~/3DViewer/ ga o'rnatish
make tests        # Barcha unit testlarni ishga tushirish
make dist         # dist/3dviewer_v2.2.tar.gz arxiv yaratish
make clean        # Vaqtinchalik fayllarni o'chirish
make uninstall    # O'rnatilgan fayllarni o'chirish
make dvi          # Hujjatni chiqarish
```

### CMake bilan qurilish
```bash
cd src
mkdir build && cd build
cmake ..
cmake --build . -j$(nproc)
ctest --output-on-failure   # Testlar
```

### Qt qmake bilan qurilish
```bash
cd src
qmake 3dviewer.pro
make -j$(nproc)
```

## Xususiyatlar

### Modellar
- OBJ fayl yuklash (vertices, normals, UV, face)
- Standart figuralar: Sphere, Cylinder, Cone, Cube, Pyramid
- Bir vaqtda maksimal **6 ta model** ko'rsatish

### Transformatsiyalar
- Alohida model uchun: Translate, Rotate, Scale
- Butun sahna uchun: Translate, Rotate, Scale (origin atrofida)

### Ko'rsatish rejimlari
- Wireframe (simli)
- Flat Shading
- Gouraud Shading
- Phong Shading

### Yorug'lik
- 1 ta yo'nalishli yorug'lik (directional)
- Global ambient yorug'lik
- Maksimal 5 ta nuqtaviy yorug'lik (point lights)

### Kamera
- Markaziy (perspective) proyeksiya
- Parallel (ortho) proyeksiya
- Sichqoncha bilan aylantirish va zoom

### Material xususiyatlari
- Base color
- Shaffoflik (transparency)
- Sindirish indeksi (refraction index)
- Aks ettirish (reflectivity)
- Yuzaki g'adir-budur (roughness)

### Ray Tracing
- Ko'p oqimli (multi-threaded) rendering
- KD-daraxt orqali tezlashtirilgan nur-uchburchak kesishish
- Aks etish (reflection) va sindirish (refraction) ko'p marotaba
- Soya hisoblash
- Chiqish formatlari: PNG, JPEG, BMP
- Maksimal ruxsat: 1920×1440

### Sozlamalar
- Fon rangi
- Yon chiziq uslubi (rang, qalinlik, uzuq/to'liq)
- Uchlar uslubi (none/circle/square, rang, hajm)
- Dastur yopilganda avtomatik saqlanadi

## Namunalar

```bash
# Dasturni ishga tushirish
./3dviewer

# Testlarni ishga tushirish
make tests
./tests/test_runner
```
