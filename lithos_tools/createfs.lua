#!/usr/bin/env lua

local lfs = require("lfs")

function procLine(ln)
   ln = ln:gsub('\\', "\\\\")
   ln = ln:gsub('\"', "\\\"")
   return ln
end

function procFile(out, dir, fname)
   out:write("\"" .. dir .. '/' .. fname .. "\" =")
   for ln in io.lines(dir .. '/' .. fname) do
      out:write("\n   \"" .. procLine(ln) .. "\\n\"")
   end
   out:write(";\n");
end

function procDir(out, dir)
   for fname in lfs.dir(dir) do
      local attr = lfs.attributes(dir .. '/' .. fname)

      if fname:sub(1, 1) ~= '.' then
         if attr.mode == "directory" then
               procDir(out, dir .. '/' .. fname)
         elseif attr.mode == "file" then
            procFile(out, dir, fname)
         end
      end
   end
end

function main(out)
   out:write("[default]\n\n")
   procDir(out, "lithos_fs")
end

main(io.open("language.fs.txt", "w"))

-- EOF
