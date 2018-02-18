# PiHttp2Server
Http2 server for Raspberry Pi based on nghttp2.

Cross compilation is done using Docker.

Basic file server is mounted on top of http2:

{::nomarkdown}

<!DOCTYPE html>
<html>
    <head>
        <style>
                        table {               font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;               border-collapse: collapse;            }            th, td {               text-align: left;               padding: 8px;               padding-top: 12px;               padding-bottom: 12px;            }            tr:nth-child(even){background-color: #f2f2f2}            th {               background-color: #4CAF50;               color: white;            }
        </style>
    </head>
    <body>
        <h2>
            Index of /home/osmc/
        </h2>
        <table>
            <tr>
                <th>
                    Name
                </th>
                <th>
                    Size
                </th>
            </tr>
            <tr>
                <td>
                    <a class="link" href="/Directory1">
                        Directory1
                    </a>
                </td>
                <td>
                    -
                </td>
            </tr>
            <tr>
                <td>
                    <a class="link" href="/Directory2">
                        Directory2
                    </a>
                </td>
                <td>
                    -
                </td>
            </tr>
            <tr>
                <td>
                    <a class="link" href="/file1.txt">
                        file1.txt
                    </a>
                </td>
                <td>
                    6.12 KB
                </td>
            </tr>
      </table>
   </body>
</html>

{:/}

# Requirements
Docker

# Compilation
run ./build.sh

build.tgz will be generated including binary and related libraries


