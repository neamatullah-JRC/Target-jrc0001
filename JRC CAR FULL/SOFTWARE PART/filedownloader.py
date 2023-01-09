import urllib.request

# URL of the file to be downloaded
url = 'http://satelecombds.com/dashboard/login'

# Name of the local file to be saved
local_filename = 'file.php'

# Open the URL and download the file
urllib.request.urlretrieve(url, local_filename)

print("File downloaded!")
