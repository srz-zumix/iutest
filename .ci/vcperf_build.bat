call tools\VisualStudio\vcperf.bat /start /level3 iutest
%CMAKE% --build .\build
call tools\VisualStudio\vcperf.bat /stop /templates iutest iutest.etl
