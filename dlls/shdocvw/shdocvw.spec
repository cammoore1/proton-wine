name	shdocvw
type	win32
init	SHDOCVW_DllMain

import	ole32.dll
import	kernel32.dll
import	ntdll.dll

debug_channels (comimpl shdocvw)

# ordinal exports
101 stub @
102 stub @
103 stub @
104 stub @
105 stub @
106 stub HlinkFindFrame
107 stub SetShellOfflineState
108 stub AddUrlToFavorites
110 stub @
111 stub @
115 stub @
116 stub @
117 stub IEAboutBox
118 stub @
119 stub @
120 stub @
121 stub @
122 stub @
123 stub @
125 stub @
130 stub @
131 stub @
135 stub @
136 stub @
137 stub @
138 stub @
139 stub @
140 stub @
141 stub @
142 stub @
143 stub @
145 stub @
146 stub @
147 stub @
148 stub @
149 stub @
150 stub @
151 stub @
152 stub @
153 stub @
158 stub @
159 stub @
160 stub @
161 stub @
162 stub @
163 stub SHAddSubscribeFavorite
164 stub @
165 stub @
167 stub @
169 stub @
170 stub @
171 stub @
172 stub @
173 stub @
174 stub @
175 stub @
176 stub @
177 stub @
178 stub @
179 stub @
180 stub @
181 stub @
183 stub @
185 stub @
187 stub @
188 stub @
189 stub @
190 stub @
191 stub @
192 stub @
194 stub @
195 stub @
196 stub @
197 stub @
198 stub @
199 stub @
200 stub @
203 stub @
204 stub @
208 stub @
209 stub @
210 stub @
211 stub @
212 stub @
213 stub @
214 stub @
215 stub @
216 stub @
217 stub @
218 stub @
219 stub @
220 stub @
221 stub @
222 stub @
223 stub @
224 stub @
225 stub @
226 stub @

@ stdcall DllCanUnloadNow() SHDOCVW_DllCanUnloadNow
@ stdcall DllGetClassObject(long long ptr) SHDOCVW_DllGetClassObject
@ stdcall DllGetVersion(ptr) SHDOCVW_DllGetVersion
@ stdcall DllInstall(long wstr) SHDOCVW_DllInstall
@ stdcall DllRegisterServer() SHDOCVW_DllRegisterServer
@ stdcall DllUnregisterServer() SHDOCVW_DllUnregisterServer
@ stub DllRegisterWindowClasses
@ stub DoAddToFavDlg
@ stub DoAddToFavDlgW
@ stub DoFileDownload
@ stub DoFileDownloadEx
@ stub DoOrganizeFavDlg
@ stub DoOrganizeFavDlgW
@ stub HlinkFrameNavigate
@ stub HlinkFrameNavigateNHL
@ stub InstallReg_RunDLL
@ stub IEWriteErrorLog
@ stub OpenURL
@ stub SHGetIDispatchForFolder
@ stub SetQueryNetSessionCount
@ stub SoftwareUpdateMessageBox
@ stub URLQualifyA
@ stub URLQualifyW
