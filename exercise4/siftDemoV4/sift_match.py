import cv2

# Load images in grayscale
img1 = cv2.imread('box.pgm', cv2.IMREAD_GRAYSCALE)
img2 = cv2.imread('scene.pgm', cv2.IMREAD_GRAYSCALE)

# Initialize SIFT detector
sift = cv2.SIFT_create()

# Detect keypoints and descriptors
kp1, des1 = sift.detectAndCompute(img1, None)
kp2, des2 = sift.detectAndCompute(img2, None)

# Brute-Force matcher with default params
bf = cv2.BFMatcher()

# Match descriptors using k-NN
matches = bf.knnMatch(des1, des2, k=2)

# Apply Lowe's ratio test
good = []
for m, n in matches:
    if m.distance < 0.75 * n.distance:
        good.append([m])

# Draw matches
matched_img = cv2.drawMatchesKnn(img1, kp1, img2, kp2, good, None, flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)

# Show the result
cv2.imshow("SIFT Matches", matched_img)
cv2.waitKey(0)
cv2.destroyAllWindows()
