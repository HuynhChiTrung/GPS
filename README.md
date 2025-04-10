# 📡 Hệ Thống Theo Dõi Vị Trí Qua SMS Dùng ESP32, GPS và SIM800L
![image](https://github.com/user-attachments/assets/f5f0905c-b233-4d7f-898c-2f55462b22c5)


## 📘 Mô tả Dự Án

Dự án sử dụng **ESP32** để xây dựng hệ thống theo dõi và điều khiển từ xa thông qua **tin nhắn SMS**. Thiết bị có thể:

- Gửi vị trí và tốc độ di chuyển thực tế qua tin nhắn SMS khi được yêu cầu.
- Bật hoặc tắt còi báo (buzzer) từ xa.
- Hoạt động liên tục và **luôn sẵn sàng phản hồi khi người dùng gửi lệnh điều khiển**.

## 🧩 Thành Phần Phần Cứng

| Thiết bị       | Mô tả                                   |
|----------------|-------------------------------------------|
| ESP32          | Vi điều khiển trung tâm                   |
| SIM800L/SIM7600 | Mô-đun GSM nhận và gửi tin nhắn SMS      |
| GPS Module (Neo-6M hoặc tương đương) | Cung cấp dữ liệu định vị |
| Buzzer         | Còi báo                                   |
| Anten GSM + GPS| Tăng độ ổn định tín hiệu                  |

## 🔄 Giao Tiếp & Chức Năng

ESP32 thực hiện **đọc dữ liệu đồng thời từ 2 mô-đun**:
- **GPS**: Đọc liên tục vị trí, tốc độ, thời gian thực.
- **SIM800L**: Luôn giữ kết nối và lắng nghe tin nhắn điều khiển.

### 📥 Các Lệnh Điều Khiển từ Điện Thoại

| Tin nhắn gửi đến ESP32 | Chức năng                                           |
|------------------------|-----------------------------------------------------|
| `FIND`                | Gửi lại vị trí, tốc độ và thời gian từ GPS qua SMS. |
| `ON`                  | Bật buzzer cảnh báo                                 |
| `OFF`                 | Tắt buzzer                                          |

> ⚠️ **Lưu ý**: Có thể mở rộng thêm các lệnh khác như kiểm tra pin, reset hệ thống,...

## 📡 Hoạt Động

1. Người dùng gửi tin nhắn tới số điện thoại gắn trong SIM800L.
2. ESP32 nhận tin nhắn, phân tích nội dung.
3. Thực hiện hành động tương ứng:
   - Nếu là `FIND` → Lấy dữ liệu từ GPS, định dạng và gửi SMS phản hồi.
   - Nếu là `ON` → Bật buzzer.
   - Nếu là `OFF` → Tắt buzzer.

## 📤 Ví dụ tin nhắn phản hồi từ hệ thống

