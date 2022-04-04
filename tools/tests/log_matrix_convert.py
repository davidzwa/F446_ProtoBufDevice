import re
import pyperclip as pc

log = """
[15:00:00 INF] (LoraGateway.Services.SerialProcessorService)    01 00 00 00 00 00 00 00 01 01 00 00 00 01 ff ff ff ff ff ff 
[15:00:00 INF] (LoraGateway.Services.SerialProcessorService)    00 01 00 00 00 00 00 00 01 00 00 00 00 09 00 00 00 00 00 00 
[15:00:00 INF] (LoraGateway.Services.SerialProcessorService)    00 00 01 00 00 00 00 00 01 00 00 00 00 0a 00 00 00 00 00 00 
[15:00:00 INF] (LoraGateway.Services.SerialProcessorService)    00 00 00 01 00 00 00 00 00 01 00 00 00 0a 00 00 00 00 00 00 
[15:00:00 INF] (LoraGateway.Services.SerialProcessorService)    00 00 00 00 01 00 00 00 00 00 00 00 00 04 ff ff ff ff ff ff 
[15:00:00 INF] (LoraGateway.Services.SerialProcessorService)    00 00 00 00 00 01 00 00 00 00 00 00 00 05 ff ff ff ff ff ff 
[15:00:00 INF] (LoraGateway.Services.SerialProcessorService)    00 00 00 00 00 00 01 00 00 00 00 00 00 06 ff ff ff ff ff ff 
[15:00:00 INF] (LoraGateway.Services.SerialProcessorService)    00 00 00 00 00 00 00 01 01 01 00 00 00 06 ff ff ff ff ff ff 
[15:00:00 INF] (LoraGateway.Services.SerialProcessorService)    1d 0e 07 83 c1 60 30 18 0c 86 00 00 00 0c f2 f2 f2 f2 f2 f2 
[15:00:00 INF] (LoraGateway.Services.SerialProcessorService)    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
"""

# https://regexr.com/
log = log.strip() # .replace('\n','',1)
regex = '\[.{9}INF]..LoraGateway\.Services\.SerialProcessorService.{5}'
matrix_raw = re.sub(regex, "", log)
rows_raw = matrix_raw.splitlines()

rows = []
for row_raw in rows_raw:
    rows.append(row_raw.split())
    
csharp_string = "byte[,] inputBytes = {\n"
count = 0
for row in rows:
    count+=1
    row_string = "\t{ "
    for elem in row:
        row_string += "0x" + elem + ", "
    
    row_string += "}"
    if count != len(rows):
        row_string = row_string.replace(", }", " },\n")
    else:
        row_string = row_string.replace(", }", " }\n")
    
    csharp_string += row_string

csharp_string += "};"

pc.copy(csharp_string)
    
print(csharp_string)
print("String copied to clipboard", len(log))
