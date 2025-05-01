import cv2
import os
import glob

input_folder = "frames"
output_folder = "data/positive"
os.makedirs(output_folder, exist_ok=True)

image_files = sorted(glob.glob(os.path.join(input_folder, "*.jpg")))
image_index = 0
crop_index = 0
selected_roi = None
cropping = False

print("Instructions:")
print(" - Drag to select a stop sign.")
print(" - Press 's' to save, 'n' to skip, 'q' to quit.")

def click_and_crop(event, x, y, flags, param):
    global roi_start, roi_end, cropping, selected_roi

    if event == cv2.EVENT_LBUTTONDOWN:
        roi_start = (x, y)
        cropping = True

    elif event == cv2.EVENT_MOUSEMOVE and cropping:
        roi_end = (x, y)

    elif event == cv2.EVENT_LBUTTONUP:
        roi_end = (x, y)
        cropping = False
        x1, y1 = roi_start
        x2, y2 = roi_end
        selected_roi = (min(x1,x2), min(y1,y2), abs(x1 - x2), abs(y1 - y2))

cv2.namedWindow("Image")
cv2.setMouseCallback("Image", click_and_crop)


while image_index < len(image_files):
    img_path = image_files[image_index]
    image = cv2.imread(img_path)
    clone = image.copy()

    if selected_roi:
        x, y, w, h = selected_roi
        cv2.rectangle(clone, (x, y), (x + w, y + h), (0, 255, 0), 2)

    cv2.imshow("Image", clone)
    key = cv2.waitKey(1) & 0xFF

    if key == ord('s') and selected_roi:
        x, y, w, h = selected_roi
        crop = image[y:y+h, x:x+w]
        crop_path = os.path.join(output_folder, f"stop_{crop_index:04d}.jpg")
        cv2.imwrite(crop_path, crop)
        print(f"Saved: {crop_path}")
        crop_index += 1
        selected_roi = None
        image_index += 1

    elif key == ord('n'):
        selected_roi = None
        image_index += 1

    elif key == ord('q'):
        break

cv2.destroyAllWindows()
