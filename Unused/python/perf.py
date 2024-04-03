import requests
import time

# Function to measure the response time of a website
def measure_response_time(url):
    try:
        start_time = time.time()
        response = requests.get(url)
        end_time = time.time()
        response_time = end_time - start_time
        return response_time
    except Exception as e:
        print(f"Error: {e}")
        return None

# Function to monitor website performance
def monitor_performance(url, interval=60):
    while True:
        response_time = measure_response_time(url)
        if response_time:
            print(f"Website response time: {response_time:.2f} seconds")
        else:
            print("Failed to measure response time.")
        time.sleep(interval)

# Example usage
if __name__ == "__main__":
    website_url = "https://example.com"
    monitor_performance(website_url)
