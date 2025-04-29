import cv2

ref_img = cv2.imread('chessboard.pgm', cv2.IMREAD_GRAYSCALE)
if ref_img is None:
    print("Error: Could not load reference image.")
    exit()

sift = cv2.SIFT_create(nfeatures=500)

ref_kp, ref_des = sift.detectAndCompute(ref_img, None)

bf = cv2.BFMatcher()

cap = cv2.VideoCapture(0)
if not cap.isOpened():
    print("Error: Could not open the camera")
    exit()

print("Press 'q' to quit")
while True:
    ret, frame = cap.read()
    if not ret:
        break

    gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    frame_kp, frame_des = sift.detectAndCompute(gray_frame, None)

    if frame_des is not None and len(frame_des) >= 2:
        matches = bf.knnMatch(ref_des, frame_des, k=2)

        good_matches = []
        for m, n in matches:
            if m.distance < 0.75 * n.distance:
                good_matches.append([m])

        good_matches = good_matches[:50]

        match_frame = cv2.drawMatchesKnn(ref_img, ref_kp, frame, frame_kp, good_matches, None, flags=2)
        cv2.imshow("SIFT Matches (Image vs Live Camera)", match_frame)
    else:
        cv2.imshow("SIFT Matches (Image vs Live Camera)", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
