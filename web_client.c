#include <curl/curl.h>

int main(void)
{
        CURL *easy = curl_easy_init();
        curl_mime *mime;
        curl_mimepart *part;

        /* Build an HTTP form with a single field named "data", */
        mime = curl_mime_init(easy);

        part = curl_mime_addpart(mime);
        curl_mime_name(part, "first_name");
        curl_mime_data(part, "youngho", CURL_ZERO_TERMINATED);

        part = curl_mime_addpart(mime);
        curl_mime_name(part, "last_name");
        curl_mime_data(part, "park", CURL_ZERO_TERMINATED);

        part = curl_mime_addpart(mime);
        curl_mime_name(part, "position");
        curl_mime_data(part, "center backc", CURL_ZERO_TERMINATED);

        part = curl_mime_addpart(mime);
        curl_mime_name(part, "number");
        curl_mime_data(part, "17", CURL_ZERO_TERMINATED);

        part = curl_mime_addpart(mime);
        curl_mime_name(part, "username");
        curl_mime_data(part, "user2", CURL_ZERO_TERMINATED);

        part = curl_mime_addpart(mime);
        curl_mime_name(part, "image");
        curl_mime_filename(part, "./1.png");

        {
                FILE *fp = fopen("1.png", "r");
                char buf[8192];
                int len = fread(buf, 1, sizeof(buf), fp);
                printf("len : %d\n", len);
                fclose(fp);

                curl_mime_data(part, buf, len);
        }

        /* Post and send it. */
        curl_easy_setopt(easy, CURLOPT_MIMEPOST, mime);
        curl_easy_setopt(easy, CURLOPT_URL, "http://192.168.3.222:2000/add");
        curl_easy_perform(easy);

        /* Clean-up. */
        curl_easy_cleanup(easy);
        curl_mime_free(mime);
}
